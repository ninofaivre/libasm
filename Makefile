NA			=	nasm
NA_FLAGS	=	-felf64
FLAGS 		=	-Wall -Werror -Wextra

SRCS		=	libasm.s
OBJS		=	$(SRCS:.s=.o)
NAME		=	libasm.a

TEST		=	test
TEST_SRCS	=	main.c

%.o:			%.s
				$(NA) $(NA_FLAGS) $<

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

$(TEST):		$(NAME) $(TEST_SRCS)
				gcc $(FLAGS) -o $(TEST) $(TEST_SRCS) -L. -lasm

clean:
				rm -rf $(OBJS)

fclean:			clean
				rm -rf $(NAME) $(TEST)

re:				fclean $(NAME)

.PHONY:			clean fclean re
