#include <check.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

START_TEST(test_list_add_to_empty_list)
{
	struct s_rz_list	*head;
	char				*data;

	head = NULL;
	data = ft_strdup("Hello");
	rz_list_add(&head, data);
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_eq(head->data, data);
	ck_assert_ptr_null(head->next);
	free(data);
	free(head);
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
