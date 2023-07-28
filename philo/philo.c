#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

struct foo {
	int				f_count;
	struct timeval	time1;
	pthread_mutex_t	f_lock;
	int				f_id;
};

void	philo_eat(struct foo *vars)
{
	printf("philo %d is eating\n", vars->f_count);
}

void	philo_think(struct foo *vars)
{
	printf("philo %d is thinking\n", vars->f_count);
}

void	philo_sleep(struct foo *vars)
{
	printf("philo %d is sleeping\n", vars->f_count);
}

void	*new_philo(void *arg)
{
	struct foo *vars = arg;
	struct timeval	time2;

	pthread_mutex_lock(&(vars->f_lock));
	(vars->f_count)++;
	gettimeofday(&time2, NULL);
	printf("cur: %d\n", time2.tv_usec - vars->time1.tv_usec);
	printf("new thread!\n");
	philo_eat(arg);
	philo_think(arg);
	philo_sleep(arg);
	pthread_mutex_unlock(&(vars->f_lock));
	return (NULL);
}

void	generate_philosophers(pthread_t thread[3])
{
	size_t		i;
	struct foo	vars;

	i = 0;
	vars.f_count = 0;
	vars.f_id = 0;
	if (gettimeofday(&(vars.time1), NULL) == -1)
		return ;
	printf("sec: %d, usec: %d\n", (int)vars.time1.tv_sec, (int)vars.time1.tv_usec);
	if (pthread_mutex_init(&(vars.f_lock), NULL) != 0)
		return ;
	while (i < 3)
	{
		if (pthread_create(&thread[i], NULL, new_philo, &vars) != 0)
			return ;
		i++;
	}
}

void	retrieve_philosophers(pthread_t thread[3])
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	thread[3];

	(void)argv;
	if (argc != 5)
	{
		printf("usage: [number_of_philosophers] [time_to_die time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	generate_philosophers(thread);
	retrieve_philosophers(thread);
	printf("ending main\n");
	return (0);
}