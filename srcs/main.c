#include "libasm/libasm.h"
#include "../munit/munit.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void test_ft_strcpy(char *dst, char *src) {
  char *srcCpy = strdup(src);
  assert(strcmp(ft_strcpy(dst, src), src) == 0);
  assert(strcmp(dst, src) == 0);
  assert(strcmp(srcCpy, src) == 0);
  free(srcCpy);
}

void test_ft_write(int fd, const void *buf, size_t count) {
  errno = 0;
  int ftRes = ft_write(fd, buf, count);
  int ftErrno = errno;
  errno = 0;
  int res = write(fd, buf, count);
  assert(ftRes == res);
  assert(ftErrno == errno);
}

void test_ft_read(int fd, void *buf, size_t count) {
  errno = 0;
  int ftRes = ft_read(fd, buf, count);
  int ftErrno = errno;
  errno = 0;
  int res = read(fd, buf, count);
  assert(ftRes == res);
  assert(ftErrno == errno);
}

void ft_strcpy_tests(void) {
	{
    char dst[] = "jkljdfqkljsfdjkqskfdjljqksjfdk";
    char src[] = "";
    test_ft_strcpy(dst, src);
  }
  {
    char dst[500] = "";
    char src[] = "vvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyyyy llllllllllllllllllllooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggg sssssssssssssttttttttttttttttttttttttrrrrrrrrrrrrrrrrrrrrrrrrrrrrriiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggggggggggggggggggg";
    test_ft_strcpy(dst, src);
  }
  {
    char dst[] = "helloooooooo";
    char src[] = "hela";
    test_ft_strcpy(dst, src);
  }
  {
    char dst[30] = "";
    char src[] = "012345678901234567890123456789";
    test_ft_strcpy(dst, src);
  }
  {
    char dst[] = "bateau";
    char src[] = "avion";
    test_ft_strcpy(dst, src);
  }
}

/* void ft_strcmp_tests(void) { */
/*   test_ft_strcmp("", ""); */
/*   test_ft_strcmp("", "right"); */
/*   test_ft_strcmp("left", ""); */
/*   test_ft_strcmp("left", "right"); */
/*   test_ft_strcmp("a\0b", "a\0c"); */
/*   test_ft_strcmp("abc", "abcd"); */
/*   test_ft_strcmp("testA", "testB"); */
/*   test_ft_strcmp("testa", "testA"); */
/*   test_ft_strcmp("a", "A"); */
/*   test_ft_strcmp("a\n", "a\n"); */
/* } */

void ft_write_tests(void) {
  test_ft_write(1, NULL, 2);
  test_ft_write(42, "test", 42);
  test_ft_write(42, "test", 2);
  test_ft_write(-1, "test", 2);
  test_ft_write(1, "test", -1);
  test_ft_write(1, "test", 0);
  test_ft_write(42, "test", 0);
  test_ft_write(1, NULL, 0);
  {
    char buffa[10];
    char buffb[10];
    int tube[2];

    pipe(tube);
    ft_write(tube[1], "test", 4);
    buffa[read(tube[0], buffa, 6)] = '\0';
    write(tube[1], "test", 4);
    buffb[read(tube[0], buffb, 6)] = '\0';
    assert(strcmp(buffa, buffb) == 0);
    close(tube[0]);
    close(tube[1]);
  }

  test_ft_write(1, "ft_write tests passed !\n", 24);
}

void ft_read_tests(void) {
  test_ft_read(-1, NULL, 42);
  {
    char buff[500];
    char buffa[22];
    char buffb[22];
    int tube[2];

    pipe(tube);
    memset(buff, 'a', 84);
    write(tube[1], buff, 84);
    test_ft_read(tube[0], NULL, 42);
    test_ft_read(tube[0], NULL, -42);
    buffa[ft_read(tube[0], buffa, 21)] = '\0';
    buffb[read(tube[0], buffb, 21)] = '\0';
    assert(strcmp(buffa, buffb) == 0);
    close(tube[0]);
    close(tube[1]);
  }
}

static MunitResult ft_strlen_test(const MunitParameter params[], void *fixture) {
	(void)fixture;

	char *str = ((char **)params)[0];
	munit_assert_int(ft_strlen(str), ==, strlen(str));
	return MUNIT_OK;
}

static MunitResult ft_strcmp_test_generic(const MunitParameter params[], void *fixture) {
	(void)fixture;

	char *left = ((char **)params)[0];
	char *right = ((char **)params)[1];

	int ft_res = ft_strcmp(left, right);
	ft_res = (ft_res < 0) ? -1 : (ft_res > 0) ? 1 : 0;
	int res = strcmp(left, right);
	res = (res < 0) ? -1 : (res > 0) ? 1 : 0;
	munit_assert_int(ft_res, ==, res);
	return MUNIT_OK;
}

static MunitResult ft_func_wrapper_test_register(const MunitParameter params[], void *fixture) {
	(void)params;

	munit_logf(MUNIT_LOG_INFO, "%s\n", "If an assertion fail, it means you are not restoring (push/pop) some callee-saved registers.");

	void (*ft_func_wrapper)(void) = fixture;
	int rbx, r12, r13, r14, r15;

	asm("pushq %rbx;"
			"pushq %r12;"
			"pushq %r13;"
			"pushq %r14;"
			"pushq %r15;");
	asm("mov $42, %rbx;"
			"mov $42, %r12;"
			"mov $42, %r13;"
			"mov $42, %r14;"
			"mov $42, %r15;");
	ft_func_wrapper();
	asm("movl %%ebx, %0;"
			"movl %%r12d, %1;"
			"movl %%r13d, %2;"
			"movl %%r14d, %3;"
			"movl %%r15d, %4;"
			: "=r" (rbx),
				"=r" (r12),
				"=r" (r13),
				"=r" (r14),
				"=r" (r15));
	asm("popq %r15;"
			"popq %r14;"
			"popq %r13;"
			"popq %r12;"
			"popq %rbx;");

	munit_assert_int(rbx, ==, 42);
	munit_assert_int(r12, ==, 42);
	munit_assert_int(r13, ==, 42);
	munit_assert_int(r14, ==, 42);
	munit_assert_int(r15, ==, 42);

	return MUNIT_OK;
}

static void *ft_strdup_test_setup(const MunitParameter params[], void *fixture) {
	(void)fixture;
	char *str = ((char **)params)[0];
	return strdup(str);
}

static void ft_strdup_test_tear_down(void *fixture) {
	free(fixture);
}

static MunitResult ft_strdup_test(const MunitParameter params[], void *fixture) {
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

static char *strs[] = {
	"",
	"test",
	"vvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyyyy llllllllllllllllllllooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggg sssssssssssssttttttttttttttttttttttttrrrrrrrrrrrrrrrrrrrrrrrrrrrrriiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggggggggggggggggggg",
	"test\0wrong",
	"\0\0\0",
	"42",
	"left",
	"right",
	"testA",
	"testB",
	NULL
};

static MunitParameterEnum one_str_test_params[] = {
	{ "str", strs },
	{ NULL, NULL }
};

static MunitParameterEnum two_str_test_params[] = {
	{ "left", strs },
	{ "right", strs },
	{ NULL, NULL }
};

static void strcmp_func_wrapper(void) {
	ft_strcmp("testA", "testB");
}

static void *ft_strcmp_test_register_setup() {
	return &strcmp_func_wrapper;
}

MunitTest tests[] = {
	{
		"/ft_strlen",
		ft_strlen_test,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		one_str_test_params
	}, {
		"/ft_strcmp/generic",
		ft_strcmp_test_generic,
		NULL,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		two_str_test_params
	}, {
		"/ft_strcmp/register",
		ft_func_wrapper_test_register,
		ft_strcmp_test_register_setup,
		NULL,
		MUNIT_TEST_OPTION_NONE,
		NULL
	}, {
		"/ft_strdup",
		ft_strdup_test,
		ft_strdup_test_setup,
		ft_strdup_test_tear_down,
		MUNIT_TEST_OPTION_NONE,
		one_str_test_params
	},
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


int main(int argc, char **argv) {

	const MunitSuite suite = {
		"/all",
		tests,
		NULL,
		1,
		MUNIT_SUITE_OPTION_NONE
	};

	return munit_suite_main(&suite, NULL, argc, argv);
}
