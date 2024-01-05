#pragma once

#include <stddef.h>

extern size_t ft_strlen(char *str);
extern int ft_strcmp(char *left, char *right);
extern char *ft_strcpy(char *dst, char *src);
extern size_t ft_write(int fd, const void *buf, size_t count);
extern size_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(char *src);
