#include "philo.h"

int	philo_eat_even(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t	now;
	pthread_mutex_lock(&(forks[philo->philo_id - 1]->lock));
	if (print_msg_takefork(philo, state) == -1)
		return (-1);
	pthread_mutex_lock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	if (print_msg_takefork(philo, state) == -1)
		return (-1);
	now = get_cur_time();
	pthread_mutex_lock(&philo->lock);
	philo->ttd = now + condition.timetodie * 1000;
	pthread_mutex_unlock(&philo->lock);
	if (print_msg_eat(philo, state, now) == -1)
		return (-1);
	wait_until(now + condition.timetoeat * 1000);
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
	return (0);
}

int	philo_eat_odd(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t	now;

	pthread_mutex_lock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	if (print_msg_takefork(philo, state) == -1)
		return (-1);
	pthread_mutex_lock(&(forks[philo->philo_id - 1]->lock));
	if (print_msg_takefork(philo, state) == -1)
		return (-1);
	now = get_cur_time();
	pthread_mutex_lock(&philo->lock);
	philo->ttd = now + condition.timetodie * 1000;
	pthread_mutex_unlock(&philo->lock);
	if (print_msg_eat(philo, state, now) == -1)
		return (-1);
	wait_until(now + condition.timetoeat * 1000);
	pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	return (0);
}

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
	if (print_msg_sleep(philo, state) == -1)
		return (-1);
	wait_until(get_cur_time() + condition.timetosleep * 1000);
	(void)forks;
	return (0);
}

void	*new_philo_even(void *arg)
{
	t_info *info = arg;

	info->philo->ttd = get_cur_time() * 1000;
	while (1)
	{
		if (philo_eat_even(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_sleep(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_think(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
	}
	return (NULL);
}

void	*new_philo_odd(void *arg)
{
	t_info *info = arg;

	info->philo->ttd = get_cur_time() * 1000;
	while (1)
	{
		if (philo_eat_odd(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_sleep(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_think(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
	}
	return (NULL);
}