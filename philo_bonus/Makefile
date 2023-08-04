NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror  
#  -fsanitize=thread -g
SRCS = main.c \
		ft_prepare.c \
		ft_generate.c \
		ft_process.c \
		ft_eat.c \
		ft_sleep_think.c \
		ft_print_msg.c \
		ft_time.c \
		ft_cleanup.c

OBJS = $(SRCS:%.c=%.o)

INCLUDES = philo_bonus.h

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all
