#include "philo.h"

t_fork	**create_forks(size_t numofphilo)
{
	size_t	i;
	t_fork	**forks;

	forks = malloc(sizeof(t_fork *) * numofphilo);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < numofphilo)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (forks[i] == NULL)
			return (free_forks_and_return_null(forks, i));
		forks[i]->fork_id = i + 1;
		if (pthread_mutex_init(&(forks[i]->lock), NULL) != 0)
			return (free_forks_and_return_null(forks, i));
		i++;
	}
	return (forks);
}

t_philo	**generate_philosophers(pthread_t **threads, t_condition condition, t_fork **forks, t_state *state)
{
	size_t		i;
	t_philo		*philo;
	t_philo		**philo_array;
	t_info		**info_array;

	i = 0;
	philo_array = malloc(sizeof(t_philo *) * condition.numofphilo);
	if (philo_array == NULL)
		return (free_forks_and_return_null(forks, condition.numofphilo));
	info_array = malloc(sizeof(t_info *) * condition.numofphilo);
	if (info_array == NULL)
	{
		free(philo_array);
		return (free_forks_and_return_null(forks, condition.numofphilo));
	}
	while (i < condition.numofphilo)
	{
		philo = malloc(sizeof(t_philo));
		if (philo == NULL)
		{
			free_threads(threads, i);
			free_infos(info_array, i);
			free_philos(philo_array, i);
			return (free_forks_and_return_null(forks, condition.numofphilo));
		}
		philo->philo_id = i + 1;
		philo->ttd = 0;
		if (pthread_mutex_init(&(philo->lock), NULL) != 0)
		{
			free_threads(threads, i);
			free_infos(info_array, i);
			free_philos(philo_array, i);
			return (free_forks_and_return_null(forks, condition.numofphilo));
		}

		philo_array[i] = philo;

		info_array[i] = malloc(sizeof(t_info));
		if (info_array[i] == NULL)
		{
			free_threads(threads, i);
			free_infos(info_array, i);
			free_philos(philo_array, i);
			return (free_forks_and_return_null(forks, condition.numofphilo));
		}
		info_array[i]->forks = forks;
		info_array[i]->philo = philo;
		info_array[i]->condition = condition;
		info_array[i]->state = state;

		threads[i] = malloc(sizeof(pthread_t));
		if (threads[i] == NULL)
		{
			free_threads(threads, i);
			free_infos(info_array, i);
			free_philos(philo_array, i);
			return (free_forks_and_return_null(forks, condition.numofphilo));
		}
		if ((i + 1) % 2 == 0)
		{
			if (pthread_create(threads[i], NULL, new_philo_even, info_array[i]) != 0)
			{
				free_threads(threads, i);
				free_infos(info_array, i);
				free_philos(philo_array, i);
				return (free_forks_and_return_null(forks, condition.numofphilo));
			}
		}
		else
		{
			if (pthread_create(threads[i], NULL, new_philo_odd, info_array[i]) != 0)
			{
				free_threads(threads, i);
				free_infos(info_array, i);
				free_philos(philo_array, i);
				return (free_forks_and_return_null(forks, condition.numofphilo));
			}
		}
		i++;
	}
	return (philo_array);
}