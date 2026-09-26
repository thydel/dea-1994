/*
 * Points
 */

#define POINTS_MAXDIM 3

#define X 0			/* indice of dimension 1 coord */
#define Y 1
#define Z 2

typedef struct {
  int magic;			/* signature */
  int dim;			/* number of dimension of cube */
  int cnt;			/* number of points */
  int size;			/* memory size */
  int* coord;			/* actual data */
  int free_flag;		/* free struct space when deleting */
} Points;

/*
 * Cub
 */

#define CUB_MAXDIM POINTS_MAXDIM

typedef struct {
  int magic;			/* signature */
  int dim;			/* number of dimension of cube */
  int side;			/* log2 of side */
  int mask;			/* mask to get bits for side */
  int elt;			/* log2 of the of an element */
  int log[CUB_MAXDIM + 1];	/* log2 of side^0...MAXDIM */
  int size[CUB_MAXDIM + 1];	/* log2 of size^0...MAXDIM */
  unsigned char* data;		/* actual cube data */
  int error;			/* function put error code here */
  int free_flag;		/* free struct space when deleting */
} Cub;

Points *Points_new(Points *zis, int dim, int cnt);
void Points_delete(Points *zis);
FILE *Points_print(Points *zis, FILE *out);
Cub *Cub_check(Cub *zis);
Cub *Cub_check3(Cub *zis, int x, int y, int z);
Cub *Cub_check_dim(Cub *zis, int dim);
Cub *Cub_check_side(Cub *zis, Cub *cub);
Cub *Cub_new(Cub *zis, int dim, int side, int elt);
Cub *Cub_volume_new(Cub *zis, int side, int elt);
Cub *Cub_plane_new(Cub *zis, int side, int elt);
Cub *Cub_line_new(Cub *zis, int side, int elt);
Cub *Cub_plane_new_from_volume(Cub *zis, Cub *volume);
Cub *Cub_line_new_from_volume(Cub *zis, Cub *volume);
void Cub_delete(Cub *zis);
FILE *Cub_print(Cub *zis, FILE *out);
Cub *Cub_permut(Cub *zis, int *p);
Cub *Cub_nopermut(Cub *zis);
Cub *Cub_line_ramp(Cub* zis);
Cub *Cub_zero(Cub *zis);
Cub *Cub_read(Cub *zis, int fd);
Cub *Cub_write(Cub *zis, int fd);
Cub *Cub_write_pgm(Cub *zis, int fd);
int Cub_cut_line(Cub *zis, char *line, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_cut_line_m(Cub *zis, char *line, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_line_points(Cub *zis, Points *out, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_sum_line(Cub *zis, int *sum, int x1, int y1, int z1, int x2, int y2, int z2);
int Cub_cut_plane(Cub *zis, Cub *plane, int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4);
int Cub_cut_plane_m(Cub *zis, Cub *plane, int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4);
Cub* Cub_cut_perimeter(Cub* zis, Cub* plane, int x, int y, int z, int n);
Cub* Cub_cut_perimeter_move(Cub* zis, Cub* plane,
		       int x1, int y1, int z1,
		       int x2, int y2, int z2,
		       int n);
