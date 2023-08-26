NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=thread -g
SRCS = main.c \
		ft_prepare.c \
		ft_generate.c \
		ft_thread.c \
		ft_eat.c \
		ft_eat_utils.c \
		ft_sleep_think.c \
		ft_print_msg.c \
		ft_monitor.c \
		ft_time.c \
		ft_cleanup.c \
		ft_atoi.c

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
