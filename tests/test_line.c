#include <check.h>
#include <stdlib.h>
#include "../get_next_line.h"

START_TEST(test_line_negative_fd)
{
	char	*line;
	int		result;

	line = NULL;
	result = get_next_line(-1, &line);
	ck_assert_int_eq(result, -1);
	ck_assert_ptr_null(line);
}
END_TEST

START_TEST(test_line_null_line)
{
	int		result;

	result = get_next_line(0, NULL);
	ck_assert_int_eq(result, -1);
}
END_TEST

Suite *line_suite(void)
{
	Suite *s;
	TCase *tc_line_error_params;

	s = suite_create("Line");
	tc_line_error_params = tcase_create("Line error params");
	tcase_add_test(tc_line_error_params, test_line_negative_fd);
	tcase_add_test(tc_line_error_params, test_line_null_line);

	tc_line_error_params = tcase_create("Line one buf size");

	suite_add_tcase(s, tc_line_error_params);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *suite;
	SRunner *srunner;

	suite = line_suite();
	srunner = srunner_create(suite);
	srunner_run_all(srunner, CK_NORMAL);
	number_failed = srunner_ntests_failed(srunner);
	srunner_free(srunner);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
