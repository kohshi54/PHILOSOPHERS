#include "philo.h"

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