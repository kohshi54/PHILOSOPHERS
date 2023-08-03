#include "philo.h"

int	philo_think(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	if (print_msg_think(philo, state) == -1)
		return (-1);
	(void)forks;
	(void)condition;
	return (0);
}

int	philo_sleep(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t now;
	now = 0;
	if (print_msg_sleep(philo, state, &now) == -1)
		return (-1);
	wait_until(now + condition.timetosleep * 1000);
	(void)forks;
	return (0);
}