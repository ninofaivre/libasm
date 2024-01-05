#include "munit.h"
#include "mandatory/mandatory.h"

/* void test_ft_strcpy(char *dst, char *src) { */
/*   char *srcCpy = strdup(src); */
/*   assert(strcmp(ft_strcpy(dst, src), src) == 0); */
/*   assert(strcmp(dst, src) == 0); */
/*   assert(strcmp(srcCpy, src) == 0); */
/*   free(srcCpy); */
/* } */
/*  */
/* void test_ft_write(int fd, const void *buf, size_t count) { */
/*   errno = 0; */
/*   int ftRes = ft_write(fd, buf, count); */
/*   int ftErrno = errno; */
/*   errno = 0; */
/*   int res = write(fd, buf, count); */
/*   assert(ftRes == res); */
/*   assert(ftErrno == errno); */
/* } */
/*  */
/* void test_ft_read(int fd, void *buf, size_t count) { */
/*   errno = 0; */
/*   int ftRes = ft_read(fd, buf, count); */
/*   int ftErrno = errno; */
/*   errno = 0; */
/*   int res = read(fd, buf, count); */
/*   assert(ftRes == res); */
/*   assert(ftErrno == errno); */
/* } */
/*  */
/* void ft_strcpy_tests(void) { */
/* 	{ */
/*     char dst[] = "jkljdfqkljsfdjkqskfdjljqksjfdk"; */
/*     char src[] = ""; */
/*     test_ft_strcpy(dst, src); */
/*   } */
/*   { */
/*     char dst[500] = ""; */
/*     char src[] = "vvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyyyy llllllllllllllllllllooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggg sssssssssssssttttttttttttttttttttttttrrrrrrrrrrrrrrrrrrrrrrrrrrrrriiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggggggggggggggggggg"; */
/*     test_ft_strcpy(dst, src); */
/*   } */
/*   { */
/*     char dst[] = "helloooooooo"; */
/*     char src[] = "hela"; */
/*     test_ft_strcpy(dst, src); */
/*   } */
/*   { */
/*     char dst[30] = ""; */
/*     char src[] = "012345678901234567890123456789"; */
/*     test_ft_strcpy(dst, src); */
/*   } */
/*   { */
/*     char dst[] = "bateau"; */
/*     char src[] = "avion"; */
/*     test_ft_strcpy(dst, src); */
/*   } */
/* } */
/*  */
/* void ft_write_tests(void) { */
/*   test_ft_write(1, NULL, 2); */
/*   test_ft_write(42, "test", 42); */
/*   test_ft_write(42, "test", 2); */
/*   test_ft_write(-1, "test", 2); */
/*   test_ft_write(1, "test", -1); */
/*   test_ft_write(1, "test", 0); */
/*   test_ft_write(42, "test", 0); */
/*   test_ft_write(1, NULL, 0); */
/*   { */
/*     char buffa[10]; */
/*     char buffb[10]; */
/*     int tube[2]; */
/*  */
/*     pipe(tube); */
/*     ft_write(tube[1], "test", 4); */
/*     buffa[read(tube[0], buffa, 6)] = '\0'; */
/*     write(tube[1], "test", 4); */
/*     buffb[read(tube[0], buffb, 6)] = '\0'; */
/*     assert(strcmp(buffa, buffb) == 0); */
/*     close(tube[0]); */
/*     close(tube[1]); */
/*   } */
/*  */
/*   test_ft_write(1, "ft_write tests passed !\n", 24); */
/* } */
/*  */
/* void ft_read_tests(void) { */
/*   test_ft_read(-1, NULL, 42); */
/*   { */
/*     char buff[500]; */
/*     char buffa[22]; */
/*     char buffb[22]; */
/*     int tube[2]; */
/*  */
/*     pipe(tube); */
/*     memset(buff, 'a', 84); */
/*     write(tube[1], buff, 84); */
/*     test_ft_read(tube[0], NULL, 42); */
/*     test_ft_read(tube[0], NULL, -42); */
/*     buffa[ft_read(tube[0], buffa, 21)] = '\0'; */
/*     buffb[read(tube[0], buffb, 21)] = '\0'; */
/*     assert(strcmp(buffa, buffb) == 0); */
/*     close(tube[0]); */
/*     close(tube[1]); */
/*   } */
/* } */

int main(int argc, char **argv) {

	MunitSuite mandatory[] = {
		ft_strlen_test_suite,
		ft_strcmp_test_suite,
		ft_strdup_test_suite,
		{ NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }
	};

	MunitSuite mandatory_suite = {
		"/mandatory",
		NULL,
		mandatory,
		1,
		MUNIT_SUITE_OPTION_NONE,
	};

	MunitSuite bonus[] = {
		{ NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }
	};

	MunitSuite bonus_suite = {
		"/bonus",
		NULL,
		bonus,
		1,
		MUNIT_SUITE_OPTION_NONE
	};

	MunitSuite all[] = {
			mandatory_suite,
			bonus_suite,
			{ NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }
	};

	const MunitSuite all_suite = {
		"/all",
		NULL,
		all,
		1,
		MUNIT_SUITE_OPTION_NONE
	};
	
	return munit_suite_main(&all_suite, NULL, argc, argv);
}
