#include "philo_bonus.h"

int	philo_think(t_philo *philo, sem_t *print)
{
	print_msg_think(philo, print);
	return (0);
}

int	philo_sleep(t_philo *philo, t_condition condition, sem_t *print)
{
	time_t now;

	now = print_msg_sleep(philo, print);
	wait_until(now + condition.timetosleep * 1000);
	return (now);
}