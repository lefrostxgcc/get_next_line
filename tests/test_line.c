#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line.h"
#include "read.h"

START_TEST(test_line_negative_fd)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;

	file = rz_open_fd(-1);
	line = NULL;
	result = get_next_line(file, &line, rz_read);
	ck_assert_int_eq(result, -1);
	ck_assert_ptr_null(line);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_null_line)
{
	struct	s_rz_file	*file;
	int					result;

	file = rz_open_fd(0);
	result = get_next_line(file, NULL, rz_read);
	ck_assert_int_eq(result, -1);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_empty_buf)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;
	char				buf[] = {EOF};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line = NULL;
	result = get_next_line(file, &line, rz_read);
	ck_assert_int_eq(result, 0);
	ck_assert_ptr_null(line);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_one_line)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;
	char				buf[] = {'h', 'e', 'l', 'l', 'o', '\n', EOF};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line = NULL;
	result = get_next_line(file, &line, rz_read);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "hello");
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_one_line_without_lf)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;
	char				buf[] = {'h', 'e', 'l', 'l', 'o', EOF};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line = NULL;
	result = get_next_line(file, &line, rz_read);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "hello");
	rz_close_fd(file);
}
END_TEST

Suite *line_suite(void)
{
	Suite *s;
	TCase *tc_line_error_params;
	TCase *tc_line_one_buf;

	s = suite_create("Line");
	tc_line_error_params = tcase_create("Line error params");
	tcase_add_test(tc_line_error_params, test_line_negative_fd);
	tcase_add_test(tc_line_error_params, test_line_null_line);

	tc_line_one_buf = tcase_create("Line one buf size");
	tcase_add_test(tc_line_one_buf, test_line_empty_buf);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_one_line);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_one_line_without_lf);

	suite_add_tcase(s, tc_line_error_params);
	suite_add_tcase(s, tc_line_one_buf);

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
