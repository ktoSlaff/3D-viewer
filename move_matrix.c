#include "s21_3DViewer.h"

int move_matrix(object_t *object) {
  int out = 0;
  if (object->vertex) {
    for (int i = 0; i < object->vertex_qty; i = i + 3) {
      object->vertex[i] += object->move[0];
      object->vertex[1 + i] += object->move[1];
      object->vertex[2 + i] += object->move[2];
    }
  } else {
    out = 1;
  }
  return out;
}