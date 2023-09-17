#include "./s21_3DViewer.h"

int parsing_file(object_t *object, char *file_path) {
  int out = 0;
  FILE *file = fopen(file_path, "r");
  if (file) {
    char line[255];
    while (fgets(line, 255, file)) {
      if (line[0] == 'v' && line[1] == ' ') {
        parsing_vertex(object, line);
        object->vertex_count++;
      }
      if (line[0] == 'f' && line[1] == ' ') {
        parsing_facets(object, line);
        object->facets_count++;
      }
    }
    fclose(file);
  } else {
    out = 1;  // File not open
  }
  return out;
}

void parsing_vertex(object_t *object, char *line) {
  line++;
  double x[3] = {0};
  sscanf(line, "%lf %lf %lf", &x[0], &x[1], &x[2]);
  for (int i = 0; i < 3; i++) {
    object->vertex_qty++;
    object->vertex =
        realloc(object->vertex, object->vertex_qty * sizeof(object->vertex[0]));
    object->vertex[object->vertex_qty - 1] = x[i];
  }
}

void parsing_facets(object_t *object, char *line) {
  char *str = NULL;
  char *sep = " ";
  str = strtok(line, sep);
  str = strtok(NULL, sep);
  int first = 0;
  int f = 0;
  while (str != NULL) {
    sscanf(str, "%d", &f);
    if (first == 0) {
      first = f;
      object->facets_qty++;
      object->facets = realloc(object->facets,
                               object->facets_qty * sizeof(object->facets[0]));
      object->facets[object->facets_qty - 1] = f - 1;
    } else {
      object->facets_qty++;
      object->facets = realloc(object->facets,
                               object->facets_qty * sizeof(object->facets[0]));
      object->facets[object->facets_qty - 1] = f - 1;
      object->facets_qty++;
      object->facets = realloc(object->facets,
                               object->facets_qty * sizeof(object->facets[0]));
      object->facets[object->facets_qty - 1] = f - 1;
    }
    str = strtok(NULL, sep);
  }
  object->facets_qty++;
  object->facets =
      realloc(object->facets, object->facets_qty * sizeof(object->facets[0]));
  object->facets[object->facets_qty - 1] = first - 1;
}

int init_object(object_t *object) {
  int out = 0;
  object->vertex = NULL;
  object->facets = NULL;
  object->vertex_qty = 0;
  object->vertex_count = 0;
  object->facets_qty = 0;
  object->facets_count = 0;
  object->scale = 1;
  for (int i = 0; i < 3; i++) {
    object->angles[i] = 0;
    object->move[i] = 0;
    object->line_color[i] = 0;
    object->vertex_color[i] = 0;
    object->vertex_color[i] = 0;
    object->background_color[i] = 1;
  }
  object->projection = 0;
  object->line_type = 0;
  object->line_width = 1;
  object->vertex_type = 0;
  object->vertex_size = 1;
  object->line_color[3] = 1;
  object->vertex_color[3] = 1;
  object->vertex_color[3] = 1;
  object->background_color[3] = 1;

  return out;
}