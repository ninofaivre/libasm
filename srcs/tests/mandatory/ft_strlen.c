#include "mandatory.h"
#include "libasm.h"
#include "tests.h"

/* GENERIC */

static MunitResult generic(const MunitParameter params[], void *fixture) {
	(void)fixture;

	char *str = ((char **)params)[0];

	munit_assert_int(ft_strlen(str), ==, strlen(str));

	return MUNIT_OK;
}

static const MunitTest generic_test = {
	"/generic",
	generic,
	NULL,
	NULL,
	MUNIT_TEST_OPTION_NONE,
	one_str_test_params
};

/* GENERIC */

/* REGISTERS */

static void register_wrapper(void) {
	ft_strlen("QUARANTE-DEUX");
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

/* PRESERVATION */

static void *preservation_setup(const MunitParameter params[], void *fixture) {
	(void)params;
	(void)fixture;

	return strdup("QUARANTE-DEUX");
}

static MunitResult preservation(const MunitParameter params[], void *fixture) {
	(void)params;

	char *str = (char *)fixture;

	ft_strlen(str);

	munit_assert_string_equal(str, "QUARANTE-DEUX");

	return MUNIT_OK;
}

static const MunitTest preservation_test = {
	"/preservation",
	preservation,
	preservation_setup,
	free,
	MUNIT_TEST_OPTION_NONE,
	NULL
};

/* PRESERVATION */

static MunitTest tests[] = {
	generic_test,
	register_test,
	preservation_test,
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

const MunitSuite ft_strlen_test_suite = {
	"/ft_strlen",
	tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};
