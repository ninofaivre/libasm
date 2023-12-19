#include "ft_libAsm.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

extern int ft_test(char *);

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

int main(void) {
  /* strlen */
  test_ft_strlen("test");
  test_ft_strlen("bonjour\n");
  test_ft_strlen("");
  test_ft_strlen("test\0test\n\0");
  test_ft_strlen("42");

  printf("ft_strlen tests passed !\n");
  /* strlen */

  /* strcpy */
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

  printf("ft_strcpy tests passed !\n");
  /* strcpy */

  /* strcmp */
  test_ft_strcmp("left", "right");
  test_ft_strcmp("", "");
  test_ft_strcmp("a\0b", "a\0c");
  test_ft_strcmp("abc", "abcd");
  test_ft_strcmp("testA", "testB");
  test_ft_strcmp("testa", "testA");
  test_ft_strcmp("a", "A");
  test_ft_strcmp("a\n", "a\n");

  printf("ft_strcmp tests passed !\n");
  /* strcmp */

  /* write */
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
  /* write */

  /* read */
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

  printf("ft_read tests passed !\n");
  /* read */

  /* strdup */
  test_ft_strdup("test");
  test_ft_strdup("");
  test_ft_strdup("test\0wrong");
  test_ft_strdup("\0\0\0");

  printf("ft_strdup tests passed !\n");
  /* strdup */

  return 0;
}
