#include "mandatory.h"
#include "libasm.h"
#include "tests.h"

/* GENERIC */

typedef struct s_generic_fixture {
	char *dst;
	char *ftDst;
} t_generic_fixture;

static MunitResult generic(const MunitParameter params[], void *fixture) {
	t_generic_fixture *fix = fixture;
	char *src = ((char **)params)[1];

	char *strcpyRet = strcpy(fix->dst, src);
	char *ftStrcpyRet = strcpy(fix->ftDst, src);

	munit_assert_string_equal(strcpyRet, ftStrcpyRet);
	munit_assert_string_equal(fix->dst, fix->ftDst);
	munit_assert_string_equal(src, fix->ftDst);
	munit_assert_ptr_not_equal(src, fix->ftDst);

	return MUNIT_OK;
}

static void *generic_setup(const MunitParameter params[], void *fixture) {
	(void)fixture;

	char *dst = ((char **)params)[0];
	size_t dstLen = strlen(dst);
	char *src = ((char **)params)[1];
	size_t srcLen = strlen(src);
	size_t dstMallocLen = (srcLen > dstLen) ? srcLen : dstLen;

	t_generic_fixture *newFixture = malloc(sizeof(t_generic_fixture));
	newFixture->dst = malloc(sizeof(char) * (dstMallocLen + 1));
	newFixture->ftDst = malloc(sizeof(char) * (dstMallocLen + 1));
	strcpy(newFixture->dst, dst);
	strcpy(newFixture->ftDst, dst);
	return newFixture;
}

static void generic_tear_down(void *fixture) {
	t_generic_fixture *fix = fixture;
	free(fix->ftDst);
	free(fix->dst);
	free(fix);
}

static const MunitTest generic_test = {
	"/generic",
	generic,
	generic_setup,
	generic_tear_down,
	MUNIT_TEST_OPTION_NONE,
	two_str_test_params	
};

/* GENERIC */

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
	generic_test,
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
