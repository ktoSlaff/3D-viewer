#ifndef SRC_S21_3DVIEWER_H_
#define SRC_S21_3DVIEWER_H_

#define S21_EPS 1e-6

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct matrix_struct {
//   double **matrix;
//   int rows;
//   int columns;
// } matrix_t;

typedef struct object_struct {
  double *vertex;
  int vertex_qty;
  int vertex_count;
  int *facets;
  int facets_qty;
  int facets_count;
  double angles[3];
  double move[3];
  double scale;
  int projection;
  int line_type;
  double line_color[4];
  int line_width;
  int vertex_type;
  double vertex_color[4];
  double vertex_size;
  double background_color[4];
} object_t;

typedef struct minmax_struct {
  double min_x;
  double max_x;
  double min_y;
  double max_y;
  double min_z;
  double max_z;
} minmax;

int parsing_file(object_t *object, char *file_path);
void parsing_vertex(object_t *object, char *line);
void parsing_facets(object_t *object, char *line);
int init_object(object_t *object);

void min_max(object_t *object, minmax *mnmx);
void normalization(object_t *object);
int move_matrix(object_t *object);
int turn_matrix(object_t *object);
int scale_matrix(object_t *object);

#endif  // SRC_S21_3DVIEWER_H_