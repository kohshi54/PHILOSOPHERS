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
	size_t			eat_count;
	pthread_mutex_t	lock;
}	t_philo;

typedef	struct	s_condition
{
	size_t	numofphilo;
	time_t	timetodie;
	time_t	timetoeat;
	time_t	timetosleep;
	size_t	numtoeat;
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

/* ft_prepare.c */
int		validate_input(int argc, char *argv[]);
void	init_condition(t_condition *conditon, int argc, char *argv[]);
bool	init_state(t_state *state);

/* ft_generate.c */
t_fork	**create_forks(size_t numofphilo);
t_philo	**generate_philosophers(pthread_t **threads, t_condition condition, t_fork **forks, t_state *state);

/* ft_thread.c */
void	*new_philo_even(void *arg);
void	*new_philo_odd(void *arg);

/* ft_eat.c */
int	philo_eat_even(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
int	philo_eat_odd(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);

/* ft_sleep_think.c */
int	philo_think(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);
int	philo_sleep(t_philo *philo, t_fork **forks, t_condition condition, t_state *state);

/* ft_print_msg.c */
int	print_msg_takefork(t_philo *philo, t_state *state);
int	print_msg_eat(t_philo *philo, t_state *state, time_t *now);
int	print_msg_sleep(t_philo *philo, t_state *state, time_t *now);
int	print_msg_think(t_philo *philo, t_state *state);

/* ft_monitor.c */
bool	check_all_philo_has_eaten_at_least_counttoeat(t_philo **philo_array, t_condition condition);
void	monitor_philos(t_philo **philo_array, t_condition condition, t_state *state, int argc);

/* ft_time.c */
time_t	get_cur_time();
void	wait_until(time_t until);

/* ft_cleanup.c */
void	retrieve_philosophers(pthread_t **philo_threads, t_condition condition);

#endif