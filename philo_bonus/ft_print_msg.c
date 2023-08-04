#include "philo_bonus.h"

time_t	print_msg_takefork(t_philo *philo, sem_t *print)
{
	time_t	now;

	now = get_cur_time();
	sem_wait(print);
	printf("%ld %zu has taken a fork\n", now / 1000, philo->philo_id);
	sem_post(print);
	return (0);
}

time_t	print_msg_eat(t_philo *philo, sem_t *print)
{
	time_t	now;

	now = get_cur_time();
	sem_wait(print);
	printf("%ld %zu is eating\n", now / 1000, philo->philo_id);
	sem_post(print);
	return (now);
}

time_t	print_msg_sleep(t_philo *philo, sem_t *print)
{
	time_t	now;

	now = get_cur_time();
	sem_wait(print);
	printf("%ld %zu is sleeping\n", now / 1000, philo->philo_id);
	sem_post(print);
	return (now);
}

time_t	print_msg_think(t_philo *philo, sem_t *print)
{
	time_t	now;

	now = get_cur_time();
	sem_wait(print);
	printf("%ld %zu is thinking\n", now / 1000, philo->philo_id);
	sem_wait(print);
	return (0);
}
