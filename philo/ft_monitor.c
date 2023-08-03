#include "philo.h"

bool	check_all_philo_has_eaten_at_least_counttoeat(t_philo **philo_array, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		if (philo_array[i]->eat_count < condition.numtoeat)
			return (false);
		i++;
	}
	return (true);
}

void	monitor_philos(t_philo **philo_array, t_condition condition, t_state *state, int argc)
{
	size_t	i;
	time_t	now;

	while (1)
	{
		i = 0;
		while (i < condition.numofphilo)
		{
			pthread_mutex_lock(&(philo_array[i]->lock));
			now = get_cur_time();
			if (philo_array[i]->ttd <= now && philo_array[i]->ttd != 0)
			{
				pthread_mutex_lock(&state->lock);
				state->alive = false;
				pthread_mutex_unlock(&state->lock);
				printf("ttd: %ld, now: %ld\n", philo_array[i]->ttd, now);
				printf("%ld %zu died\n", now / 1000, philo_array[i]->philo_id);
				pthread_mutex_unlock(&philo_array[i]->lock);
				return ;
			}
			pthread_mutex_unlock(&philo_array[i]->lock);
			i++;
		}
		if (argc == 6)
		{
			if (check_all_philo_has_eaten_at_least_counttoeat(philo_array, condition) == true)
			{
				pthread_mutex_lock(&state->lock);
				state->alive = false;
				pthread_mutex_unlock(&state->lock);
				return ;
			}
		}
	}
}