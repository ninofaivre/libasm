NA			=	nasm
NA_FLAGS	=	-felf64
CFLAGS 		=	-Wall -Werror -Wextra

SRCS		=	srcs/libasm/libasm.s
OBJS		=	$(SRCS:.s=.o)
NAME		=	libasm.a

TEST		=	test
TEST_SRCS	=	srcs/main.c munit/munit.c srcs/tests/tests.c \
						srcs/tests/mandatory/ft_strlen.c \
						srcs/tests/mandatory/ft_strcmp.c \
						srcs/tests/mandatory/ft_strdup.c \
						srcs/tests/mandatory/ft_strcpy.c \

%.o:			%.s
				$(NA) $(NA_FLAGS) $<

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

$(TEST):		$(NAME) $(TEST_SRCS)
				gcc $(CFLAGS) -o $(TEST) $(TEST_SRCS) -L. -lasm -I./munit -I./srcs/tests -I./srcs/libasm

clean:
				rm -rf $(OBJS)

fclean:			clean
				rm -rf $(NAME) $(TEST)

re:				fclean $(NAME)

# exec this rule every time makefile has changed
# and you want to generate compile_commands.json
# (config build for clangd lsp)
bear:			fclean
	bear -- make test

.PHONY:			clean fclean re
