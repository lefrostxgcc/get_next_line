#include <check.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

static struct s_rz_list	*head;
static const char head_data[] = "Hello";

void setup_add_list(void)
{
	rz_list_add(&head, head_data, sizeof head_data);
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
	ck_assert_ptr_null(head->next);
	ck_assert_ptr_ne(head->data, head_data);
	ck_assert_mem_eq(head->data, head_data, sizeof head_data);
}
END_TEST

START_TEST(test_list_add_to_exist_list)
{
	struct s_rz_list	*node;
	const char			data[] = "World";

	node = rz_list_add(&head, data, sizeof data);

	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_nonnull(node);
	ck_assert_ptr_null(node->next);
	ck_assert_ptr_eq(head->next, node);
	ck_assert_ptr_ne(node->data, data);
	ck_assert_mem_eq(node->data, data, sizeof data);
	ck_assert_mem_eq(head->data, head_data, sizeof head_data);
	free(node->data);
	free(node);
	node = NULL;
}
END_TEST

START_TEST(test_list_free_null_head_param)
{
	rz_list_free(NULL);
}
END_TEST

START_TEST(test_list_free_null_head)
{
	struct s_rz_list	*head;

	head = NULL;
	rz_list_free(&head);
}
END_TEST

START_TEST(test_list_free_one_element_list)
{
	struct s_rz_list	*head;

	head = NULL;
	rz_list_add(&head, "abc", 4);
	rz_list_free(&head);
	ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_list_free_multi_element_list)
{
	struct s_rz_list	*head;

	head = NULL;
	rz_list_add(&head, "abc", 4);
	rz_list_add(&head, "12", 3);
	rz_list_add(&head, "wxyz", 5);
	rz_list_add(&head, "0", 2);
	rz_list_free(&head);
	ck_assert_ptr_null(head);
}
END_TEST

Suite *list_suite(void)
{
	Suite *s;
	TCase *tc_list_add;
	TCase *tc_list_free;

	s = suite_create("List");
	tc_list_add = tcase_create("List add");
	tcase_add_checked_fixture(tc_list_add, setup_add_list, teardown_add_list);
	tcase_add_test(tc_list_add, test_list_add_to_empty_list);
	tcase_add_test(tc_list_add, test_list_add_to_exist_list);

	tc_list_free = tcase_create("List free");
	tcase_add_test(tc_list_free, test_list_free_null_head_param);
	tcase_add_test(tc_list_free, test_list_free_null_head);
	tcase_add_test(tc_list_free, test_list_free_one_element_list);
	tcase_add_test(tc_list_free, test_list_free_multi_element_list);

	suite_add_tcase(s, tc_list_add);
	suite_add_tcase(s, tc_list_free);

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
