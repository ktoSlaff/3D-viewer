#include "./3DViewer_test.h"

int main(void) {
  Suite* tests_list[] = {/*create_matrix(), remove_matrix(),*/ parsing(),
                         /**/ minmax_test(), NULL};
  int failed_count = 0;

  for (int i = 0; tests_list[i] != NULL; i++) {
    SRunner* suite_runner = srunner_create(tests_list[i]);
    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }
  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
