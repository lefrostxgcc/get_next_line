#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line.h"
#include "read.h"

void setup_eline(void)
{
}

void teardown_eline(void)
{
}

void setup_line(void)
{
}

void teardown_line(void)
{
}

START_TEST(test_line_negative_fd)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;

	file = rz_open_fd(-1);
	line = NULL;
	result = get_next_line(file->fd, &line);
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
	result = get_next_line(file->fd, NULL);
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
	result = get_next_line(file->fd, &line);
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
	result = get_next_line(file->fd, &line);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "hello");
	free(line);
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
	result = get_next_line(file->fd, &line);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "hello");
	free(line);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_two_line)
{
	struct	s_rz_file	*file;
	char				*line_abc;
	char				*line_de;
	int					result_abc;
	int					result_de;
	char				buf[] = {'a', 'b', 'c', '\n', 'd', 'e', '\n', EOF};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line_abc = line_de = NULL;
	result_abc = get_next_line(file->fd, &line_abc);
	result_de = get_next_line(file->fd, &line_de);
	ck_assert_int_eq(result_abc, 1);
	ck_assert_pstr_eq(line_abc, "abc");
	ck_assert_int_eq(result_de, 1);
	ck_assert_pstr_eq(line_de, "de");
	free(line_de);
	free(line_abc);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_three_line)
{
	struct	s_rz_file	*file;
	char				*line_abc;
	char				*line_de;
	char				*line_fgh;
	int					result_abc;
	int					result_de;
	int					result_fgh;
	char				buf[] =
	{
		'a', 'b', 'c', '\n', 'd', 'e', '\n', 'f', 'g', 'h', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line_abc = line_de = line_fgh = NULL;
	result_abc = get_next_line(file->fd, &line_abc);
	result_de = get_next_line(file->fd, &line_de);
	result_fgh = get_next_line(file->fd, &line_fgh);
	ck_assert_int_eq(result_abc, 1);
	ck_assert_pstr_eq(line_abc, "abc");
	ck_assert_int_eq(result_de, 1);
	ck_assert_pstr_eq(line_de, "de");
	ck_assert_int_eq(result_fgh, 1);
	ck_assert_pstr_eq(line_fgh, "fgh");
	free(line_fgh);
	free(line_de);
	free(line_abc);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_two_buf_one_line)
{
	struct	s_rz_file	*file;
	char				*line;
	int					result;
	char				buf[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line = NULL;
	result = get_next_line(file->fd, &line);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "0123456789ABCDEF0123");
	free(line);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_two_buf_two_line)
{
	struct	s_rz_file	*file;
	char				*line1;
	char				*line2;
	int					result1;
	int					result2;
	char				buf[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n',
		'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line1 = line2 = NULL;
	result1 = get_next_line(file->fd, &line1);
	result2 = get_next_line(file->fd, &line2);
	ck_assert_int_eq(result1, 1);
	ck_assert_pstr_eq(line1, "0123456789");
	ck_assert_int_eq(result2, 1);
	ck_assert_pstr_eq(line2, "ABCDEF0123");
	free(line1);
	free(line2);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_four_buf_two_line)
{
	struct	s_rz_file	*file;
	char				*line1;
	char				*line2;
	int					result1;
	int					result2;
	char				buf[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n',
		'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line1 = line2 = NULL;
	result1 = get_next_line(file->fd, &line1);
	result2 = get_next_line(file->fd, &line2);
	ck_assert_int_eq(result1, 1);
	ck_assert_pstr_eq(line1, "0123456789");
	ck_assert_int_eq(result2, 1);
	ck_assert_pstr_eq(line2, "ABCDEF0123456789abcdef");
	free(line1);
	free(line2);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_four_buf_three_line)
{
	struct	s_rz_file	*file;
	char				*line1;
	char				*line2;
	char				*line3;
	int					result1;
	int					result2;
	int					result3;
	char				buf[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n',
		'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '\n',
		'1', '2', '3', '4', '5', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line1 = line2 = line3 = NULL;
	result1 = get_next_line(file->fd, &line1);
	result2 = get_next_line(file->fd, &line2);
	result3 = get_next_line(file->fd, &line3);
	ck_assert_int_eq(result1, 1);
	ck_assert_pstr_eq(line1, "0123456789");
	ck_assert_int_eq(result2, 1);
	ck_assert_pstr_eq(line2, "ABCDEF0123456789abcdef");
	ck_assert_int_eq(result3, 1);
	ck_assert_pstr_eq(line3, "12345");
	free(line1);
	free(line2);
	free(line3);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_three_empty_line)
{
	struct	s_rz_file	*file;
	char				*line_abc;
	char				*line_de;
	char				*line_fgh;
	char				*line_eof;
	int					result_abc;
	int					result_de;
	int					result_fgh;
	int					result_eof;
	char				buf[] =
	{
		'\n', '\n', '\n', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line_abc = line_de = line_fgh = line_eof = NULL;
	result_abc = get_next_line(file->fd, &line_abc);
	result_de = get_next_line(file->fd, &line_de);
	result_fgh = get_next_line(file->fd, &line_fgh);
	result_eof = get_next_line(file->fd, &line_eof);
	ck_assert_int_eq(result_abc, 1);
	ck_assert_pstr_eq(line_abc, "");
	ck_assert_int_eq(result_de, 1);
	ck_assert_pstr_eq(line_de, "");
	ck_assert_int_eq(result_fgh, 1);
	ck_assert_pstr_eq(line_fgh, "");
	ck_assert_int_eq(result_eof, 0);
	ck_assert_ptr_null(line_eof);
	free(line_fgh);
	free(line_de);
	free(line_abc);
	rz_close_fd(file);
}
END_TEST

START_TEST(test_line_one_buf_line_three_empty_line)
{
	struct	s_rz_file	*file;
	char				*line;
	char				*line_abc;
	char				*line_de;
	char				*line_fgh;
	char				*line_ab;
	char				*line_eof;
	int					result;
	int					result_abc;
	int					result_de;
	int					result_fgh;
	int					result_ab;
	int					result_eof;
	char				buf[] =
	{
		'1', '2', '3', '\n', '\n', '\n', '\n', 'a', 'b', EOF
	};

	file = rz_open_fd(1);
	rz_set_read_buf(file, buf, sizeof buf);
	line = line_abc = line_de = line_fgh = line_ab = line_eof = NULL;
	result = get_next_line(file->fd, &line);
	result_abc = get_next_line(file->fd, &line_abc);
	result_de = get_next_line(file->fd, &line_de);
	result_fgh = get_next_line(file->fd, &line_fgh);
	result_ab = get_next_line(file->fd, &line_ab);
	result_eof = get_next_line(file->fd, &line_eof);
	ck_assert_int_eq(result, 1);
	ck_assert_pstr_eq(line, "123");
	ck_assert_int_eq(result_abc, 1);
	ck_assert_pstr_eq(line_abc, "");
	ck_assert_int_eq(result_de, 1);
	ck_assert_pstr_eq(line_de, "");
	ck_assert_int_eq(result_fgh, 1);
	ck_assert_pstr_eq(line_fgh, "");
	ck_assert_int_eq(result_ab, 1);
	ck_assert_pstr_eq(line_ab, "ab");
	ck_assert_int_eq(result_eof, 0);
	line_eof = NULL;
	ck_assert_ptr_null(line_eof);
	free(line);
	free(line_fgh);
	free(line_de);
	free(line_abc);
	free(line_ab);
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
	tcase_add_checked_fixture(tc_line_error_params, setup_eline, teardown_eline);
	tcase_add_test(tc_line_error_params, test_line_negative_fd);
	tcase_add_test(tc_line_error_params, test_line_null_line);

	tc_line_one_buf = tcase_create("Line one buf size");
	tcase_add_checked_fixture(tc_line_one_buf, setup_line, teardown_line);
	tcase_add_test(tc_line_one_buf, test_line_empty_buf);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_one_line);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_one_line_without_lf);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_two_line);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_three_line);
	tcase_add_test(tc_line_one_buf, test_line_two_buf_one_line);
	tcase_add_test(tc_line_one_buf, test_line_two_buf_two_line);
	tcase_add_test(tc_line_one_buf, test_line_four_buf_two_line);
	tcase_add_test(tc_line_one_buf, test_line_four_buf_three_line);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_three_empty_line);
	tcase_add_test(tc_line_one_buf, test_line_one_buf_line_three_empty_line);

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
