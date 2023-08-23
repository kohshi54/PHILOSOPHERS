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

t_philo	*allocate_and_set_philo(size_t i, t_condition condition)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->philo_id = i + 1;
	philo->ttd = 0;
	philo->right_fork_id = i;
	if (i + 1 == condition.numofphilo)
		philo->left_fork_id = 0;
	else
		philo->left_fork_id = i + 1;
	if (pthread_mutex_init(&(philo->lock), NULL) != 0)
		return (NULL);
	return (philo);
}

t_info	*allocat_and_set_info(t_fork **forks, t_philo *philo, t_condition condition, t_state *state)
{
	t_info	*new;

	new = malloc(sizeof(t_info));
	new->forks = forks;
	new->philo = philo;
	new->condition = condition;
	new->state = state;
	return (new);
}

t_philo	*set_philo_info_and_new_thread(size_t i, t_fork **forks, t_condition condition, t_state *state)
{
	t_philo	*new_philo;
	t_info	*new_info;

	new_philo = allocate_and_set_philo(i, condition);
	if (new_philo == NULL)
		return (NULL);
	new_info = allocat_and_set_info(forks, new_philo, condition, state);
	if (new_info == NULL)
		return (NULL);
	if ((i + 1) % 2 == 0)
	{
		if (pthread_create(&new_philo->thread_id, NULL, new_philo_even, new_info) != 0)
			return (NULL);
	}
	else
	{
		if (pthread_create(&new_philo->thread_id, NULL, new_philo_odd, new_info) != 0)
			return (NULL);
	}
	return (new_philo);
}

t_philo	**generate_philosophers(t_condition condition, t_fork **forks, t_state *state)
{
	size_t		i;
	t_philo		**philo_array;

	i = 0;
	philo_array = malloc(sizeof(t_philo *) * condition.numofphilo);
	if (philo_array == NULL)
		return (free_forks_and_return_null(forks, condition.numofphilo));
	while (i < condition.numofphilo)
	{
		philo_array[i] = set_philo_info_and_new_thread(i, forks, condition, state);
		if (philo_array[i] == NULL)
		{
			free_philos(philo_array, i);
			return (free_forks_and_return_null(forks, condition.numofphilo));
		}
		i++;
	}
	return (philo_array);
}