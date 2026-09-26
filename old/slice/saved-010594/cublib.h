/*
 * Points
 */

#define POINTS_MAXDIM 3

#define X 0			/* indice of dimension 1 coord */
#define Y 1
#define Z 2

typedef struct {
  int magic;
  int dim;
  int cnt;
  int size;
  int* coord;
} Points;

/*
 * Cub
 */

#define CUB_MAXDIM POINTS_MAXDIM

#define D1 0			/* X indice of dimension 1 data */
#define D2 1			/* Y */
#define D3 2			/* Z */
#define D0 3			/* dimension zero for zero offset
				   when permutting dimension order */

typedef struct {
  int magic;
  int dim;			/* number of dimension of cube */
  int lside;			/* log2 of side */
  int log[CUB_MAXDIM + 1];	/* log2 of side^1...MAXDIM */
  int logperm[CUB_MAXDIM + 1];	/* log2 of side^1...MAXDIM
				   permuted to get another faces of cub */
  int size[CUB_MAXDIM];		/* size of side^1...MAXDIM */
  char* data[CUB_MAXDIM];	/* actual cube data with space for
				   cut thru backward in dimensions */
  int cnt;			/* for a zero dimension accumulation */
  float ratio;			/* for a zero dimension reduction */
} Cub;

Points *Points_new(Points *zis, int dim, int cnt);
void Points_delete(Points *zis);
FILE *Points_print(Points *zis, FILE *out);
Cub *Cub_new(Cub *zis, int dim, int lside);
FILE *Cub_print(Cub *zis, FILE *out);
int Cub_permut(Cub *zis, int *p);
int Cub_nopermut(Cub *zis);
void Cub_zero_volume(Cub *zis);
void Cub_zero_plane(Cub *zis);
void Cub_zero_line(Cub *zis);
Cub *Cub_read(Cub *zis, int fd);
Cub *Cub_write(Cub *zis, int dim, int fd);
Cub *Cub_write_pgm(Cub *zis, int fd);
int Cub_cut_line(Cub *zis, char *line, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_line_points(Cub *zis, Points *out, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_sum_line(Cub *zis, int *sum, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_cut_plane(Cub *zis, int x1, int y1, int z1,
		  int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4);
