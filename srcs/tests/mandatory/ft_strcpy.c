#include "mandatory.h"
#include "libasm.h"
#include "tests.h"

/* REGISTERS */

static void register_wrapper(void) {
	char src[] = "avion";
	char dst[] = "bateau";
	ft_strcpy(dst, src);
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
	register_test,
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

const MunitSuite ft_strcpy_test_suite = {
	"/ft_strcpy",
	tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};
