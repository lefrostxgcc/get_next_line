#include <check.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

START_TEST(test_list_add_to_empty_list)
{
}
END_TEST

Suite *list_suite(void)
{
	Suite *s;
	TCase *tc_list_add;

	s = suite_create("List");
	tc_list_add = tcase_create("List add");

	tcase_add_test(tc_list_add, test_list_add_to_empty_list);
	
	suite_add_tcase(s, tc_list_add);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *suite;
	SRunner *srunner;

	suite = list_suite();
	srunner = srunner_create(suite);
	srunner_run_all(srunner, CK_NORMAL);
	number_failed = srunner_ntests_failed(srunner);
	srunner_free(srunner);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
