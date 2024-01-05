#include "tests.h"

MunitResult ft_func_wrapper_test_register(const MunitParameter params[], void *fixture) {
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
	"QUARANTE-DEUX",
	NULL
};


MunitParameterEnum one_str_test_params[] = {
	{ "str", strs },
	{ NULL, NULL }
};

MunitParameterEnum two_str_test_params[] = {
	{ "left", strs },
	{ "right", strs },
	{ NULL, NULL }
};
