#include "./s21_3DViewer.h"

void normalization(object_t *object) {
  minmax mnmx = {0};
  min_max(object, &mnmx);
  double x_mid = mnmx.min_x + (mnmx.max_x - mnmx.min_x) / 2.0;
  double y_mid = mnmx.min_y + (mnmx.max_y - mnmx.min_y) / 2.0;
  double z_mid = mnmx.min_z + (mnmx.max_z - mnmx.min_z) / 2.0;
  double x = mnmx.max_x - mnmx.min_x;
  double y = mnmx.max_y - mnmx.min_y;
  double z = mnmx.max_z - mnmx.min_z;
  double scale = x, scale_in = 0.5;
  if (y > scale) {
    scale = y;
  }
  if (z > scale) {
    scale = z;
  }
  scale = (scale_in - (scale_in * (-1))) / scale;
  for (int i = 0; i < object->vertex_qty; i = i + 3) {
    object->vertex[i] = (object->vertex[i] - x_mid) * scale;
    object->vertex[1 + i] = (object->vertex[1 + i] - y_mid) * scale;
    object->vertex[2 + i] = (object->vertex[2 + i] - z_mid) * scale;
  }
}
