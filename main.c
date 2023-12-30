#include "libasm.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void test_ft_strlen(char *str) {
  assert(ft_strlen(str) == strlen(str));
}

void test_ft_strcpy(char *dst, char *src) {
  char *srcCpy = strdup(src);
  assert(strcmp(ft_strcpy(dst, src), src) == 0);
  assert(strcmp(dst, src) == 0);
  assert(strcmp(srcCpy, src) == 0);
  free(srcCpy);
}

void test_ft_strcmp(char *left, char *right) {
  int ftRes = ft_strcmp(left, right);
  int res = strcmp(left, right);
  assert((ftRes > 0 && res > 0) ||
         (ftRes < 0 && res < 0) ||
         (ftRes == 0 && res == 0));
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

void test_ft_strdup(char *str) {
  char *ftRes = ft_strdup(str);
  char *res = strdup(str);

  assert(ftRes != res);
  assert((res != str) == (ftRes != str));
  assert(strcmp(ftRes, res) == 0);

  free(ftRes);
  free(res);
}

void ft_strlen_tests(void) {
  test_ft_strlen("");
  test_ft_strlen("vvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyyyy llllllllllllllllllllooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggg sssssssssssssttttttttttttttttttttttttrrrrrrrrrrrrrrrrrrrrrrrrrrrrriiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggggggggggggggggggg");
  test_ft_strlen("test");
  test_ft_strlen("bonjour\n");
  test_ft_strlen("test\0test\n\0");
  test_ft_strlen("42");
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

void ft_strcmp_tests(void) {
  test_ft_strcmp("", "");
  test_ft_strcmp("", "right");
  test_ft_strcmp("left", "");
  test_ft_strcmp("left", "right");
  test_ft_strcmp("a\0b", "a\0c");
  test_ft_strcmp("abc", "abcd");
  test_ft_strcmp("testA", "testB");
  test_ft_strcmp("testa", "testA");
  test_ft_strcmp("a", "A");
  test_ft_strcmp("a\n", "a\n");
}

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

void ft_strdup_tests(void) {
  test_ft_strdup("");
  test_ft_strdup("vvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyyyy llllllllllllllllllllooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggg sssssssssssssttttttttttttttttttttttttrrrrrrrrrrrrrrrrrrrrrrrrrrrrriiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggggggggggggggggggggggggggggggggggg");
  test_ft_strdup("test");
  test_ft_strdup("test\0wrong");
  test_ft_strdup("\0\0\0");
}

int exec_one_test(char *arg) {
	if (strcmp(arg, "strlen") == 0)
		ft_strlen_tests();
	else if (strcmp(arg, "strcpy") == 0)
		ft_strcpy_tests();
	else if (strcmp(arg, "strcmp") == 0)
		ft_strcmp_tests();
	else if (strcmp(arg, "write") == 0)
		ft_write_tests();
	else if (strcmp(arg, "read") == 0)
		ft_read_tests();
	else if (strcmp(arg, "strdup") == 0)
		ft_strdup_tests();
	else {
		fprintf(stderr, "invalid arg : %s\n", arg);
		return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc > 2) {
		fprintf(stderr, "wrong number of args\n");
		return 2;
	}
	if (argc > 1 && strcmp(argv[1], "all") != 0)
		return exec_one_test(argv[1]);
	ft_strlen_tests();
	printf("ft_strlen tests passed !\n");
	ft_strcpy_tests();
  printf("ft_strcpy tests passed !\n");
	ft_strcmp_tests();
  printf("ft_strcmp tests passed !\n");
	ft_write_tests();
	ft_read_tests();
  printf("ft_read tests passed !\n");
	ft_strdup_tests();
  printf("ft_strdup tests passed !\n");

  return 0;
}
