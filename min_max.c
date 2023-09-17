#include "./s21_3DViewer.h"

void min_max(object_t *object, minmax *mnmx) {
  int x = 0, y = 1, z = 2;
  mnmx->min_x = object->vertex[x];
  mnmx->max_x = mnmx->min_x;
  mnmx->min_y = object->vertex[y];
  mnmx->max_y = mnmx->min_y;
  mnmx->min_z = object->vertex[z];
  mnmx->max_z = mnmx->min_z;
  for (int i = 0; i < object->vertex_qty; i = i + 3) {
    if (object->vertex[x + i] < mnmx->min_x) {
      mnmx->min_x = object->vertex[x + i];
    }
    if (object->vertex[x + i] > mnmx->max_x) {
      mnmx->max_x = object->vertex[x + i];
    }
    if (object->vertex[y + i] < mnmx->min_y) {
      mnmx->min_y = object->vertex[y + i];
    }
    if (object->vertex[y + i] > mnmx->max_y) {
      mnmx->max_y = object->vertex[y + i];
    }
    if (object->vertex[z + i] < mnmx->min_z) {
      mnmx->min_z = object->vertex[z + i];
    }
    if (object->vertex[z + i] > mnmx->max_z) {
      mnmx->max_z = object->vertex[z + i];
    }
  }
}