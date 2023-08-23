#include "philo.h"

void	*new_philo_even(void *arg)
{
	t_info *info = arg;

	pthread_mutex_lock(&info->philo->lock);
	info->philo->ttd = get_cur_time() + info->condition.timetodie;
	pthread_mutex_unlock(&info->philo->lock);
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

	pthread_mutex_lock(&info->philo->lock);
	info->philo->ttd = get_cur_time() + info->condition.timetodie;
	pthread_mutex_unlock(&info->philo->lock);
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
