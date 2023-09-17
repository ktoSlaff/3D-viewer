#include "3DViewer_test.h"

// START_TEST(minmax_test_1) {
//   char *file_path = "./OBJ_files/cube.obj";
//   matrix_t vertex;
//   matrix_t facets;
//   parsing_file(&vertex, &facets, file_path);
//   minmax mnmx;
//   mnmx.min_x = 0;
//   mnmx.max_x = 0;
//   mnmx.min_y = 0;
//   mnmx.max_y = 0;
//   mnmx.min_z = 0;
//   mnmx.max_z = 0;
//   min_max(&vertex, &mnmx);
//   printf("%lf - %lf - %lf - %lf - %lf - %lf", mnmx.max_x, mnmx.min_x,
//          mnmx.max_y, mnmx.min_y, mnmx.max_z, mnmx.min_z);
//   s21_remove_matrix(&vertex);
//   s21_remove_matrix(&facets);
// }
// END_TEST

START_TEST(minmax_test_2) {
  char *file_path = "./OBJ_files/airboat.obj";
  object_t *object;
  object = calloc(1, sizeof(object_t));
  init_object(object);
  printf("%s\n", file_path);
  int flag = parsing_file(object, file_path);
  ck_assert_int_eq(flag, 0);
  normalization(object);
  for (int i = 0; i < object->vertex_qty; i++) {
    printf("%lf\n", object->vertex[i]);
  }
}
END_TEST

Suite *minmax_test(void) {
  Suite *suite = suite_create("\033[01;36mminmax\033[0m");
  TCase *tcase_test = tcase_create("minmax");

  //   tcase_add_test(tcase_test, minmax_test_1);
  tcase_add_test(tcase_test, minmax_test_2);

  suite_add_tcase(suite, tcase_test);
  return suite;
}