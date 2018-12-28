#include <check.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

static struct s_rz_list	*head;
static const char *head_data = "Hello";

void setup_add_list(void)
{
	rz_list_add(&head, ft_strdup(head_data));
}

void teardown_add_list(void)
{
	free(head->data);
	free(head);
	head = NULL;
}

START_TEST(test_list_add_to_empty_list)
{
	ck_assert_ptr_nonnull(head);
	ck_assert_pstr_eq(head->data, head_data);
	ck_assert_ptr_null(head->next);
}
END_TEST

Suite *list_suite(void)
{
	Suite *s;
	TCase *tc_list_add;

	s = suite_create("List");
	tc_list_add = tcase_create("List add");
	tcase_add_checked_fixture(tc_list_add, setup_add_list, teardown_add_list);
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
