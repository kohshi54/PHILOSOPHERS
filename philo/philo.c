#include "philo.h"

typedef enum e_philo_state
{
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKiNG,
	PHILO_DIED,
}	t_philo_state;

typedef struct	s_fork
{
	pthread_mutex_t	lock;
	size_t			fork_id;
}	t_fork;

typedef struct	s_philo
{
	size_t			philo_id;
	time_t			ttl;
	t_philo_state	state;
	t_fork			*forks;
}	t_philo;

typedef	struct	s_condition
{
	size_t	numofphilo;
	time_t	timetodie;
	time_t	timetoeat;
	time_t	timetosleep;
}	t_condition;

typedef struct	s_info
{
	t_philo		*philo;
	t_fork		*forks;
	t_condition	condition;
}	t_info;

void	init_vars(t_condition *conditon, char *argv[])
{
	conditon->numofphilo = atoi(argv[1]);
	conditon->timetodie = atoi(argv[2]);
	conditon->timetoeat = atoi(argv[3]);
	conditon->timetosleep = atoi(argv[4]);
}

t_fork	*create_forks(size_t numofphilo)
{
	size_t	i;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * numofphilo);
	i = 0;
	while (i < numofphilo)
	{
		forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&(forks[i].lock), NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

void	philo_eat(t_philo *philo, t_fork *forks, t_condition condition)
{
	pthread_mutex_lock(&(forks[philo->philo_id - 1].lock));
	printf("philo %zu has taken a fork\n", philo->philo_id);
	// take_left_fork();
	if (philo->philo_id == 1)
		pthread_mutex_lock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_lock(&(forks[philo->philo_id - 2].lock));
	printf("philo %zu has taken a fork\n", philo->philo_id);
	// take_right_fork();
	printf("philo %zu is eating\n", philo->philo_id);
	usleep(condition.timetoeat * 1000);
	// start_eating();
	pthread_mutex_unlock(&(forks[philo->philo_id - 1].lock));
	if (philo->philo_id == 1)
		pthread_mutex_lock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_unlock(&(forks[(philo->philo_id - 2)].lock));
}

void	philo_think(t_philo *philo, t_fork *forks, t_condition condition)
{
	printf("philo %zu is thinking\n", philo->philo_id);
	(void)forks;
	(void)condition;
}

void	philo_sleep(t_philo *philo, t_fork *forks, t_condition condition)
{
	printf("philo %zu is sleeping\n", philo->philo_id);
	usleep(condition.timetosleep * 1000);
	(void)forks;
}

void	*new_philo(void *arg)
{
	t_info *info = arg;

	while (1)
	{
		if (info->philo->state == PHILO_DIED)
			return (NULL);
		philo_eat(info->philo, info->forks, info->condition);
		info->philo->ttl = info->condition.timetodie;
		if (info->philo->state == PHILO_DIED)
			return (NULL);
		philo_sleep(info->philo, info->forks, info->condition);
		if (info->philo->state == PHILO_DIED)
			return (NULL);
		philo_think(info->philo, info->forks, info->condition);
	}
	return (NULL);
}

pthread_t	*generate_philosophers(t_condition condition, t_fork *forks)
{
	size_t		i;
	pthread_t	*philo_threads;
	t_philo		*philo_info;
	t_info		*info;

	philo_threads = malloc(sizeof(pthread_t) * condition.numofphilo);
	i = 0;
	while (i < condition.numofphilo)
	{
		philo_info = malloc(sizeof(t_philo));
		philo_info->philo_id = i + 1;
		philo_info->ttl = condition.timetodie;
		philo_info->state = PHILO_EATING;
		philo_info->forks = forks;
	
		info = malloc(sizeof(t_info));
		info->forks = forks;
		info->philo = philo_info;
		info->condition = condition;
		if (pthread_create(philo_threads, NULL, new_philo, info) != 0)
			return (NULL);
		i++;
	}
	return (philo_threads);
}

void	retrieve_philosophers(pthread_t *philo_threads, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
}

void	monitor_philos()
{
	
}

int	main(int argc, char *argv[])
{
	t_condition	condition;
	t_fork		*forks;
	pthread_t	*philo_threads;

	if (argc != 5)
	{
		printf("usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	init_vars(&condition, argv);
	forks = create_forks(condition.numofphilo);
	philo_threads = generate_philosophers(condition, forks);
	monitor_philos();
	retrieve_philosophers(philo_threads, condition);
	printf("ending main\n");
	return (0);
}