#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
#include <semaphore.h>
# include <signal.h>
# define SEM_FORK "/forks"
# define SEM_PRINT "/print"
# define SEM_MONITOR "/monitor"

typedef struct	s_philo
{
	size_t	philo_id;
	time_t	ttd;
	size_t	eat_count;
	sem_t	*lock;
}	t_philo;

typedef	struct	s_condition
{
	size_t	numofphilo;
	time_t	timetodie;
	time_t	timetoeat;
	time_t	timetosleep;
	size_t	numtoeat;
}	t_condition;

typedef struct	s_info
{
	t_philo		*philo;
	sem_t		*print;
}	t_info;

/* ft_prepare.c */
int		validate_input(int argc, char *argv[]);
void	init_condition(t_condition *conditon, int argc, char *argv[]);
bool	set_vars(t_condition *condition, int argc, char *argv[]);

/* ft_generate.c */
sem_t	*create_forks(size_t numofphilo);
// void	generate_philosophers(t_condition condition, sem_t *forks);
sem_t	*generate_philosophers(t_condition condition, sem_t *forks);

/* ft_process.c */
void	add_eat_count(t_philo *philo);
void	*monitor_thread(void *arg);
pthread_t	start_monitor_thread(t_philo *philo, sem_t *print);
// void	init_philo(t_philo *philo, t_condition condition, size_t philo_id);
char	*init_philo(t_philo *philo, t_condition condition, size_t philo_id);
void	*new_philo(size_t philo_id, t_condition condition, sem_t *forks, sem_t *print);

/* ft_eat.c */
void	set_ttd(t_philo *philo, time_t now, t_condition condition);
void	add_eat_count(t_philo *philo);
int		philo_eat(t_philo *philo, sem_t *forks, t_condition condition, sem_t *print);

/* ft_sleep_think.c */
int	philo_think(t_philo *philo, sem_t *print);
int	philo_sleep(t_philo *philo, t_condition condition, sem_t *print);

/* ft_print_msg.c */
time_t	print_msg_takefork(t_philo *philo, sem_t *print);
time_t	print_msg_eat(t_philo *philo, sem_t *print);
time_t	print_msg_sleep(t_philo *philo, sem_t *print);
time_t	print_msg_think(t_philo *philo, sem_t *print);

/* ft_monitor.c */

/* ft_time.c */
time_t	get_cur_time();
void	wait_until(time_t until);

/* ft_cleanup.c */
void	wait_for_philosophers(t_condition condition);
void	cleanup_semaphore(sem_t *fork, sem_t *print);

char	*gen_unique_sem_monitor(size_t philo_id);

#endif