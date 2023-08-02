#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct	s_fork
{
	size_t			fork_id;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct	s_philo
{
	size_t			philo_id;
	time_t			ttd;
	pthread_mutex_t	lock;
}	t_philo;

typedef	struct	s_condition
{
	size_t	numofphilo;
	time_t	timetodie;
	time_t	timetoeat;
	time_t	timetosleep;
}	t_condition;

typedef struct	s_state
{
	bool			alive;
	pthread_mutex_t	lock;
}	t_state;

typedef struct	s_info
{
	t_philo		*philo;
	t_fork		**forks;
	t_condition	condition;
	t_state		*state;
}	t_info;

time_t	get_cur_time();
void	init_condition(t_condition *conditon, char *argv[]);
t_fork	**create_forks(size_t numofphilo);
void	wait_until(time_t until);


int	philo_eat_even(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
int	philo_eat_odd(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
int	philo_think(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
int	philo_sleep(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
void	*new_philo_even(void *arg);
void	*new_philo_odd(void *arg);

int	print_msg_takefork(t_philo *philo, t_state *state);
// int	print_msg_eat(t_philo *philo, t_state *state);
int	print_msg_eat(t_philo *philo, t_state *state, time_t now);
int	print_msg_sleep(t_philo *philo, t_state *state);
int	print_msg_think(t_philo *philo, t_state *state);

#endif