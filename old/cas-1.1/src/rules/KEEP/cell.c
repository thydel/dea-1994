#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <malloc.h>
#include <memory.h>

#define DEBUG 0

typedef struct {
    char* name;
    int (*func)();
} Func;

extern Func tconex[];
extern Func tconex_size[];
int (*Func_get(Func*, char*))();

char* cmd_name;
int debug;

unsigned char* transition;
unsigned char* transition1;
unsigned char* transition2;
int* cnt_transition;
int transition_size;
int transition_size1;
int transition_size2;
unsigned char* state;
unsigned char* futur_state;

char* usage = 
    "[-s{size} <power-of-two>] [-l{oop} <int>] [-{s}k{ip} <int>] [-e{xtract} <int>] -[c{onex> <name>] -f{rame} <file> -t{ransition} <file> [-o{utput file} <file>] [-h{ist}] [-D{ebug}] [-{o}v{erlay} <0|1>] [-{s}u{m} <file>] [-{l}a{st} <file>] [-x{dump}]";

int main(int ac, char** av) {
    extern char *optarg;
    extern int optind;
    
    int c;
    int errflg;
    int side;
    int size;

    int shift;
    int loop;
    char* conex_name;
    char* frame_name;
    char* transition_name;
    char* output_name;
    char* last_name;
    int (*conex)();
    int (*conex_size)();
    int frame_file;
    int transition_file;
    int output_file;
    int sum_file;
    int last_file;
    int cnt_file;
    int skip;
    int extract;
    char* hist;
    int overlay;
    int sum;
    char* sum_name;
    char* cnt_name;
    int zoom;
    
    cmd_name = av[0];
    errflg = 0;

    shift = 8;
    loop = 1024 * 1024;
    conex_name = "moore-1";
    frame_name = "fff";
    transition_name = "ttt";
    output_name = 0;
    last_name = "last";
    skip = 0;
    extract = -1;
    hist = 0;
    overlay = 0;
    sum_name = 0;
    cnt_name = 0;
    zoom = 0;

    while ((c = getopt(ac, av, "s:l:k:e:c:f:t:o:h:Dv:u:a:n:z:")) != EOF)
	switch (c) {
	  case 's':
	    shift = atoi(optarg);
	    break;
	  case 'l':
	    loop = atoi(optarg);
	    break;
	  case 'z':
	    zoom = atoi(optarg);
	    break;
	  case 'v':
	    overlay = atoi(optarg);
	    break;
	  case 'u':
	    sum_name = malloc(strlen(optarg) + 1);
	    strcpy(sum_name, optarg);
	    break;
	  case 'a':
	    last_name = malloc(strlen(optarg) + 1);
	    strcpy(last_name, optarg);
	    break;
	  case 'n':
	    cnt_name = malloc(strlen(optarg) + 1);
	    strcpy(cnt_name, optarg);
	    break;
	  case 'k':
	    skip = atoi(optarg);
	    break;
	  case 'e':
	    extract = atoi(optarg);
	    break;
	  case 'c':
	    conex_name = malloc(strlen(optarg) + 1);
	    strcpy(conex_name, optarg);
	    break;
	  case 'f':
	    frame_name = malloc(strlen(optarg) + 1);
	    strcpy(frame_name, optarg);
	    break;
	  case 't':
	    transition_name = malloc(strlen(optarg) + 1);
	    strcpy(transition_name, optarg);
	    break;
	  case 'o':
	    output_name = malloc(strlen(optarg) + 1);
	    strcpy(output_name, optarg);
	    break;
	  case 'h':
	    hist = malloc(strlen(optarg) + 1);
	    strcpy(hist, optarg);
	    break;
	  case 'D':
	    debug = 1;
	    break;
	  case '?':
	    errflg++;
	}
    
    if (errflg) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }
    
    for (; optind < ac; optind++) {
	fprintf(stderr, "%s, usage: %s\n", cmd_name, usage);
	exit(1);
    }

    side = 1 << shift;
    size = side * side;
    state = malloc(size);
    futur_state = malloc(size);

    conex = Func_get(tconex, conex_name);
    if (!conex) {
	fprintf(stderr, "%s: %s not found\n", cmd_name, conex_name);
	exit(1);
    }
    conex_size = Func_get(tconex_size, conex_name);
    assert(conex_size);
    transition_size = conex_size();

    frame_file = open(frame_name, O_RDONLY);
    if (frame_file == -1) {
	fprintf(stderr, "%s: cannot open frame %s\n", cmd_name, frame_name);
	perror("");
	exit(1);
    }
    read(frame_file, state, size);

    transition_file = open(transition_name, O_RDONLY);
    if (transition_file == -1) {
	fprintf(stderr, "%s: cannot open transition table %s\n", cmd_name, transition_name);
	perror("");
	exit(1);
    }
    transition = malloc(transition_size);
    read(transition_file, transition, transition_size);
    cnt_transition = malloc(transition_size * sizeof(int));
    memset(cnt_transition, 0, transition_size * sizeof(int));

    if (output_name) {
	output_file = creat(output_name, 0666);
	if (output_file == -1) {
	    fprintf(stderr, "%s: cannot open output table %s\n", cmd_name, output_name);
	    perror("");
	    exit(1);
	}
    } else {
	output_file = 1;
    }

    if (sum_name) {
	sum_file = creat(sum_name, 0666);
	if (sum_file == -1) {
	    fprintf(stderr, "%s: cannot open sum file %s\n", cmd_name, sum_name);
	    perror("");
	    exit(1);
	}
    } else {
	sum_file = -1;
    }

    if (cnt_name) {
	cnt_file = creat(cnt_name, 0666);
	if (cnt_file == -1) {
	    fprintf(stderr, "%s: cannot open cnt file %s\n", cmd_name, cnt_name);
	    perror("");
	    exit(1);
	}
    } else {
	cnt_file = -1;
    }

    if (last_name) {
	last_file = creat(last_name, 0666);
	if (last_file == -1) {
	    fprintf(stderr, "%s: cannot open last file %s\n", cmd_name, last_name);
	    perror("");
	    exit(1);
	}
    } else {
	last_file = -1;
    }

    return main_loop(loop, shift, conex, skip, extract, hist, output_file, overlay, sum_file,
		     last_file, cnt_file, zoom);
}

main_loop(int loop, int shift, int (*conex)(), int skip, int do_extract, char* hist, int output_file, int overlay, int sum_file, int last_file, int cnt_file, int zoom)
{
    unsigned char* otab;
    unsigned char* tmp;
    int side;
    int size;
    int skip_cnt;
    int tsize;
    FILE* histfile;
    int* sum_tab;
    
    side = 1 << shift;
    size = side * side;
    skip_cnt = skip;
    
    if (do_extract < 16) {
	tsize = size >> 3;
    } else if (do_extract == 16) {
	tsize = size;
    } else if (do_extract == 17) {
	tsize = size;
    } else if (do_extract == 18) {
	tsize = size >> 1;
    }
    
    otab = malloc(tsize);
    
    sum_tab = malloc(size * sizeof(int));
    memset(sum_tab, 0, size * sizeof(int));
    
    if (hist) {
	histfile = fopen(hist, "w");
    }
    while (loop--) {
	if (sum_file != -1) {
	    do_sum(state, sum_tab, size);
	}
	if (skip_cnt-- == 0) {
	    skip_cnt = skip;
	    if (hist) {
		do_hist(state, histfile, size);
	    }
	    if (do_extract != -1) {
		if (do_extract == 18) {
		    extract_2(state, otab, side);
		} else {
		    te[do_extract](state, otab, size);
		}
		if (overlay) {
		    lseek(output_file, 0L, SEEK_SET);
		}
		write(output_file, otab, tsize);
	    } else {
		if (overlay) {
		    lseek(output_file, 0L, SEEK_SET);
		}
		write(output_file, state, size);
	    }
	}
	conex(state, futur_state, transition, side, size);
	tmp = state;
	state = futur_state;
	futur_state = tmp;
    }
    if (last_file != -1) {
	write(last_file, state, size);
    }
    if (cnt_file != -1) {
	write(cnt_file, cnt_transition, transition_size * sizeof(int));
    }
    if (sum_file != -1) {
	int fd, x, y;
	FILE* ascii;

	write(sum_file, sum_tab, size * sizeof(int));
	
	fd = creat("sum.ascii", 0666);
	close(fd);
	ascii = fopen("sum.ascii", "w");
	for (x = 0; x < side; ++x) {
	    for (y = 0; y < side; ++y) {
		fprintf(ascii, "%d %d %d\n", x, y, sum_tab[x * side + y]);
	    }
	}
    }
    return 0;
}

