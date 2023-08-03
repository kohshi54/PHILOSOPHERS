#include "philo.h"

void	free_philos(t_philo **philo_array, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(philo_array[i]);
		i++;
	}
	free(philo_array);
}

void	free_infos(t_info **info_array, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(info_array[i]);
		i++;
	}
	free(info_array);
}


void	free_threads(pthread_t **threads, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(threads[i]);
		i++;
	}
	free(threads);
}

void	*free_forks_and_return_null(t_fork **forks, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}

void	retrieve_philosophers(pthread_t **philo_threads, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_join(*(philo_threads[i]), NULL);
		i++;
	}
}