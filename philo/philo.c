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
	pthread_mutex_t	lock;
	size_t			philo_id;
	time_t			ttl;
	t_philo_state	state;
	struct timeval	*last_meal_time;
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
	t_philo			*philo;
	t_fork			*forks;
	t_condition		condition;
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

void	wait_until(int32_t until)
{
	struct timeval	cur;

	while (1)
	{
		gettimeofday(&cur, NULL);
		if (cur.tv_usec - until > 0)
			break ;
	}
}

int	print_msg_takefork(t_philo *philo)
{
	if (philo->state == PHILO_DIED)
		return (1);
	printf("philo %zu has taken a fork\n", philo->philo_id);
	return (0);
}

int	print_msg_eat(t_philo *philo)
{
	if (philo->state == PHILO_DIED)
		return (1);
	printf("philo %zu is eating\n", philo->philo_id);
	return (0);
}

int	print_msg_sleep(t_philo *philo)
{
	if (philo->state == PHILO_DIED)
		return (1);
	printf("philo %zu is sleeping\n", philo->philo_id);
	return (0);
}

int	print_msg_think(t_philo *philo)
{
	if (philo->state == PHILO_DIED)
		return (1);
	printf("philo %zu is thinking\n", philo->philo_id);
	return (0);
}

int	philo_eat_even(t_philo *philo, t_fork *forks, t_condition condition)
{
	if (philo->philo_id == 1)
		pthread_mutex_lock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_lock(&(forks[philo->philo_id - 2].lock));
	pthread_mutex_lock(&(forks[philo->philo_id - 1].lock));
	if (print_msg_takefork(philo) == 1)
		return (1);
	if (print_msg_takefork(philo) == 1)
		return (1);
	gettimeofday(philo->last_meal_time, NULL);
	if (print_msg_eat(philo) == 1)
		return (1);
	struct timeval	now;
	gettimeofday(&now, NULL);
	wait_until(now.tv_usec + condition.timetoeat);
	if (philo->philo_id == 1)
		pthread_mutex_unlock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_unlock(&(forks[(philo->philo_id - 2)].lock));
	pthread_mutex_unlock(&(forks[philo->philo_id - 1].lock));
	return (0);
}

int	philo_eat_odd(t_philo *philo, t_fork *forks, t_condition condition)
{
	pthread_mutex_lock(&(forks[philo->philo_id - 1].lock));
	if (print_msg_takefork(philo) == 1)
		return (1);

	if (philo->philo_id == 1)
		pthread_mutex_lock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_lock(&(forks[philo->philo_id - 2].lock));
	if (print_msg_takefork(philo) == 1)
		return (1);
	gettimeofday(philo->last_meal_time, NULL);
	if (print_msg_eat(philo) == 1)
		return (1);
	struct timeval	now;
	gettimeofday(&now, NULL);
	wait_until(now.tv_usec + condition.timetoeat);
	pthread_mutex_unlock(&(forks[philo->philo_id - 1].lock));
	if (philo->philo_id == 1)
		pthread_mutex_unlock(&(forks[condition.numofphilo - 1].lock));
	else
		pthread_mutex_unlock(&(forks[(philo->philo_id - 2)].lock));
	return (0);
}

int	philo_think(t_philo *philo, t_fork *forks, t_condition condition)
{
	if (print_msg_think(philo) == 1)
		return (1);
	(void)forks;
	(void)condition;
	return (0);
}

int	philo_sleep(t_philo *philo, t_fork *forks, t_condition condition)
{
	if (print_msg_think(philo) == 1)
		return (1);
	struct timeval	now;
	gettimeofday(&now, NULL);
	wait_until(now.tv_usec + condition.timetosleep);
	(void)forks;
	return (0);
}

void	*new_philo(void *arg)
{
	t_info *info = arg;

	gettimeofday(info->philo->last_meal_time, NULL);
	while (1)
	{
		pthread_mutex_lock(&info->philo->lock);
		if (info->philo->state == PHILO_DIED)
		{
			pthread_mutex_unlock(&info->philo->lock);
			break ;
		}
		pthread_mutex_unlock(&info->philo->lock);
		info->philo->ttl = info->condition.timetodie;
		if (info->philo->philo_id % 2 == 1)
		{
			if (philo_eat_odd(info->philo, info->forks, info->condition) == 1)
				break ;
		}
		else
		{
			if (philo_eat_even(info->philo, info->forks, info->condition) == 1)
				break ;
		}
		pthread_mutex_lock(&info->philo->lock);
		if (info->philo->state == PHILO_DIED)
		{
			pthread_mutex_unlock(&info->philo->lock);
			break ;
		}
		if (philo_sleep(info->philo, info->forks, info->condition) == 1)
			break ;
		pthread_mutex_lock(&info->philo->lock);
		if (info->philo->state == PHILO_DIED)
		{
			pthread_mutex_unlock(&info->philo->lock);
			break ;
		}
		pthread_mutex_unlock(&info->philo->lock);
		if (philo_think(info->philo, info->forks, info->condition) == 1)
			break ;
	}
	printf("end philo id: %zu\n", info->philo->philo_id);
	return (NULL);
}

t_philo	**generate_philosophers(pthread_t **philo_threads, t_condition condition, t_fork *forks)
{
	size_t		i;
	t_philo		*philo_info;
	t_info		*info;
	t_philo		**philo_array;

	i = 0;
	philo_array = malloc(sizeof(t_philo *) * condition.numofphilo);
	while (i < condition.numofphilo)
	{
		philo_info = malloc(sizeof(t_philo));
		philo_info->philo_id = i + 1;
		philo_info->ttl = condition.timetodie;
		philo_info->state = PHILO_EATING;
		philo_info->forks = forks;
		philo_info->last_meal_time = malloc(sizeof(struct timeval));
		gettimeofday(philo_info->last_meal_time, NULL);
		if (pthread_mutex_init(&(philo_info->lock), NULL) != 0)
			return (NULL);

		philo_array[i] = philo_info;

		info = malloc(sizeof(t_info));
		info->forks = forks;
		info->philo = philo_info;
		info->condition = condition;

		philo_threads[i] = malloc(sizeof(pthread_t));
		if (pthread_create(philo_threads[i], NULL, new_philo, info) != 0)
			return (NULL);
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
		pthread_join(*philo_threads[i], NULL);
		i++;
	}
}

void	stop_all_thread(t_philo **philo_array, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_mutex_lock(&philo_array[i]->lock);
		philo_array[i]->state = PHILO_DIED;
		pthread_mutex_unlock(&philo_array[i]->lock);
		i++;
	}
}

void	monitor_philos(t_philo **philo_array, t_condition condition)
{
	size_t			i;
	struct timeval	curtime;

	while (1)
	{
		i = 0;
		while (i < condition.numofphilo)
		{
			pthread_mutex_lock(&philo_array[i]->lock);
			gettimeofday(&curtime, NULL);
			if (curtime.tv_usec - philo_array[i]->last_meal_time->tv_usec > condition.timetodie * 1000)
			{
				pthread_mutex_unlock(&philo_array[i]->lock);
				printf("cur: %d, lmt: %d, ttd: %ld\n", curtime.tv_usec, philo_array[i]->last_meal_time->tv_usec, condition.timetodie * 1000);
				printf("philo id %zu dead\n", i + 1);
				stop_all_thread(philo_array, condition);
				return ;
			}
			pthread_mutex_unlock(&philo_array[i]->lock);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_condition	condition;
	t_fork		*forks;
	pthread_t	**philo_threads;
	t_philo		**philo_array;

	if (argc != 5)
	{
		printf("usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	init_vars(&condition, argv);
	forks = create_forks(condition.numofphilo);
	philo_threads = malloc(sizeof(pthread_t *) * condition.numofphilo);
	philo_array = generate_philosophers(philo_threads, condition, forks);
	monitor_philos(philo_array, condition);
	retrieve_philosophers(philo_threads, condition);
	printf("ending main\n");
	return (0);
}