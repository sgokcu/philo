NAME	=	philo
SRC		=	main.c utils.c philo.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	gcc
CFLAGS 	=	-Wall -Wextra -Werror -fsanitize=thread -g
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re