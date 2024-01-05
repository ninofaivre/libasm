#include "mandatory.h"
#include "libasm.h"
#include "tests.h"

/* GENERIC */

static void *generic_setup(const MunitParameter params[], void *fixture) {
	(void)fixture;

	char *str = ((char **)params)[0];

	return strdup(str);
}

static MunitResult generic(const MunitParameter params[], void *fixture) {
	char *str_param = ((char **)params)[0];
	char *str = (char *)fixture;
	char *ft_str = ft_strdup(str);

	munit_assert_string_equal(str, ft_str);
	munit_assert_string_equal(str, str_param);
	munit_assert_ptr_not_equal(str, str_param);
	munit_assert_ptr_not_equal(str, ft_str);
	munit_assert_ptr_not_equal(str_param, ft_str);

	free(ft_str);

	return MUNIT_OK;
}

static const MunitTest generic_test = {
	"/generic",
	generic,
	generic_setup,
	free,
	MUNIT_TEST_OPTION_NONE,
	one_str_test_params
};

/* GENERIC */

/* REGISTERS */

static void register_wrapper(void) {
	free(ft_strdup("QUARANTE-DEUX"));
}

static void *register_setup(const MunitParameter params[], void *fixture) {
	(void)params;
	(void)fixture;
	return &register_wrapper;
};

static const MunitTest register_test = {
	"/registers",
	ft_func_wrapper_test_register,
	register_setup,
	NULL,
	MUNIT_TEST_OPTION_NONE,
	NULL
};

/* REGISTERS */

static MunitTest tests[] = {
	generic_test,
	register_test,
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

const MunitSuite ft_strdup_test_suite = {
	"/ft_strdup",
	tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};
