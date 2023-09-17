
#include "3DViewer_test.h"

START_TEST(parsing_test_1) {
  char *file_path = "./OBJ_files/cube.obj";
  object_t *object;
  object = calloc(1, sizeof(object_t));
  init_object(object);
  printf("%s\n", file_path);
  int flag = parsing_file(object, file_path);
  ck_assert_int_eq(flag, 0);
  // for (int i = 0; i < object->vertex_qty; i++) {
  //   printf("%lf\n", object->vertex[i]);
  // }
  // for (int i = 0; i < object->facets_qty; i++) {
  //   printf("%d ", object->facets[i]);
  //   // if (i % 3 == 0) {
  //   //   printf("\n");
  //   // }
  // }
  // printf("%d\n", object->vertex_count);
  // printf("%d\n", object->facets_count);
  free(object->vertex);
  free(object->facets);
  free(object);
}
END_TEST

Suite *parsing(void) {
  Suite *suite = suite_create("\033[01;36mPARSING\033[0m");
  TCase *tcase_test = tcase_create("PARSING");

  tcase_add_test(tcase_test, parsing_test_1);

  suite_add_tcase(suite, tcase_test);
  return suite;
}
