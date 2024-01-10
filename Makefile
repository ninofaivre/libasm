NAME = libasm.a
TEST = test
BEAR = compile_commands.json

NA = nasm
NA_FLAGS = -felf64

CC = gcc
CFLAGS = -Wall -Werror -Wextra
CINCLUDE_DIR = munit srcs/tests srcs/libasm
CINCLUDES = $(addprefix -I./, $(CINCLUDE_DIR))

SRCS = srcs/libasm/libasm.s
OBJS = $(SRCS:.s=.o)

TEST_SRCS	=	srcs/main.c munit/munit.c srcs/tests/tests.c \
						srcs/tests/mandatory/ft_strlen.c \
						srcs/tests/mandatory/ft_strcmp.c \
						srcs/tests/mandatory/ft_strdup.c \
						srcs/tests/mandatory/ft_strcpy.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(NAME)

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< $(CINCLUDES) -o $@

$(OBJS): %.o: %.s
	$(NA) $(NA_FLAGS) $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(TEST): $(NAME) $(TEST_OBJS)
	gcc $(TEST_OBJS) $(CFLAGS) -L. -lasm -o $(TEST)

clean:
	rm -rf $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -rf $(NAME) $(TEST)

re: fclean $(NAME)

# exec this rule every time makefile has changed
# and you want to generate compile_commands.json
# (config build for clangd lsp)
bear: $(BEAR)

$(BEAR): Makefile
	make fclean
	bear -- make test

.PHONY: clean fclean re
