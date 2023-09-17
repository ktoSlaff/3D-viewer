#include "s21_3DViewer.h"

int scale_matrix(object_t *object) {
  int out = 0;
  if (object->vertex) {
    if (object->scale > S21_EPS) {
      for (int i = 0; i < object->vertex_qty; i++) {
        object->vertex[i] *= object->scale;
      }
    } else {
      out = 2;
    }
  } else {
    out = 1;
  }
  return out;
}