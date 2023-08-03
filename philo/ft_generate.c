#include "philo.h"

t_fork	**create_forks(size_t numofphilo)
{
	size_t	i;
	t_fork	**forks;

	forks = malloc(sizeof(t_fork *) * numofphilo);
	i = 0;
	while (i < numofphilo)
	{
		forks[i] = malloc(sizeof(t_fork));
		forks[i]->fork_id = i + 1;
		if (pthread_mutex_init(&(forks[i]->lock), NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

t_philo	**generate_philosophers(pthread_t **threads, t_condition condition, t_fork **forks, t_state *state)
{
	size_t		i;
	t_philo		*philo;
	t_info		*info;
	t_philo		**philo_array;

	i = 0;
	philo_array = malloc(sizeof(t_philo *) * condition.numofphilo);
	while (i < condition.numofphilo)
	{
		philo = malloc(sizeof(t_philo));
		philo->philo_id = i + 1;
		philo->ttd = 0;
		if (pthread_mutex_init(&(philo->lock), NULL) != 0)
			return (NULL);

		// printf("philo %zu created!\n", philo->philo_id);

		philo_array[i] = philo;

		info = malloc(sizeof(t_info));
		info->forks = forks;
		info->philo = philo;
		info->condition = condition;
		info->state = state;

		threads[i] = malloc(sizeof(pthread_t));
		if ((i + 1) % 2 == 0)
		{
			if (pthread_create(threads[i], NULL, new_philo_even, info) != 0)
				return (NULL);
		}
		else
		{
			if (pthread_create(threads[i], NULL, new_philo_odd, info) != 0)
				return (NULL);			
		}
		i++;
	}
	return (philo_array);
}