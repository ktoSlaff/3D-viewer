#include "s21_3DViewer.h"
// https://ru.wikipedia.org/wiki/%D0%9C%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0_%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0
int turn_matrix(object_t *object) {
  int out = 0;
  double deg = M_PI / 180;
  if (object->vertex) {
    double x1 = cos(object->angles[1] * deg) * cos(object->angles[2] * deg);
    double x2 = sin(object->angles[0] * deg) * sin(object->angles[1] * deg) *
                    cos(object->angles[2] * deg) +
                sin(object->angles[2] * deg) * cos(object->angles[0] * deg);
    double x3 = sin(object->angles[0] * deg) * sin(object->angles[2] * deg) -
                sin(object->angles[1] * deg) * cos(object->angles[0] * deg) *
                    cos(object->angles[2] * deg);
    double y1 = -sin(object->angles[2] * deg) * cos(object->angles[1] * deg);
    double y2 = -sin(object->angles[0] * deg) * sin(object->angles[1] * deg) *
                    sin(object->angles[2] * deg) +
                cos(object->angles[0] * deg) * cos(object->angles[2] * deg);
    double y3 = sin(object->angles[0] * deg) * cos(object->angles[2] * deg) +
                sin(object->angles[1] * deg) * sin(object->angles[2] * deg) *
                    cos(object->angles[0] * deg);
    double z1 = sin(object->angles[1] * deg);
    double z2 = -sin(object->angles[0] * deg) * cos(object->angles[1] * deg);
    double z3 = cos(object->angles[0] * deg) * cos(object->angles[1] * deg);
    for (int i = 0; i < object->vertex_qty; i = i + 3) {
      double x = object->vertex[i];
      double y = object->vertex[1 + i];
      double z = object->vertex[2 + i];
      object->vertex[i] = x * x1 + y * y1 + z * z1;
      object->vertex[1 + i] = x * x2 + y * y2 + z * z2;
      object->vertex[2 + i] = x * x3 + y * y3 + z * z3;
    }
  } else {
    out = 1;
  }
  return out;
}