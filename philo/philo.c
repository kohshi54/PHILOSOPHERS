#include "philo.h"

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

void	monitor_philos(t_philo **philo_array, t_condition condition, t_state *state)
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
			if (philo_array[i]->ttd <= now)
			{
				printf("ttd: %ld, now: %ld\n", philo_array[i]->ttd, now);
				pthread_mutex_lock(&state->lock);
				state->alive = false;
				pthread_mutex_unlock(&state->lock);
				printf("%ld %zu died\n", now / 1000, philo_array[i]->philo_id);
				pthread_mutex_unlock(&philo_array[i]->lock);
				return ;
			}
			pthread_mutex_unlock(&philo_array[i]->lock);
			i++;
		}
	}
}

void	init_state(t_state *state)
{
	state->alive = 1;
	if (pthread_mutex_init(&(state->lock), NULL) != 0)
		exit(0);

}

int	main(int argc, char *argv[])
{
	t_fork		**forks;
	t_condition	condition;
	t_state		state;
	pthread_t	**threads;
	t_philo		**philo_array;

	if (argc != 5)
	{
		printf("usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	init_condition(&condition, argv);
	init_state(&state);
	forks = create_forks(condition.numofphilo);
	threads = malloc(sizeof(pthread_t *) * condition.numofphilo);
	philo_array = generate_philosophers(threads, condition, forks, &state);
	monitor_philos(philo_array, condition, &state);
	retrieve_philosophers(threads, condition);
	printf("ending main\n");
	return (0);
}