NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
SRCS = philo.c
OBJS = $(SRCS:%.c=%.o)

INCLUDES = philo.h

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all
