#include "philo.h"

time_t	get_cur_time()
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_usec);
}

void	init_condition(t_condition *conditon, char *argv[])
{
	conditon->numofphilo = atoi(argv[1]);
	conditon->timetodie = atoi(argv[2]);
	conditon->timetoeat = atoi(argv[3]);
	conditon->timetosleep  = atoi(argv[4]);
}

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

void	wait_until(time_t until)
{
	struct timeval	cur;

	while (1)
	{
		gettimeofday(&cur, NULL);
		if (until <= cur.tv_usec)
			break ;
	}
}