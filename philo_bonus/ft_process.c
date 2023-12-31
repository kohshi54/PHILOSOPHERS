#include "philo_bonus.h"

void	*monitor_thread(void *arg)
{
	t_info	*info;
	t_philo	*philo;
	time_t	now;
	sem_t	*print;

	info = (t_info *)arg;
	philo = info->philo;
	print = info->print;
	while (1)
	{
		sem_wait(philo->lock);
		now = get_cur_time();
		if (philo->ttd < now)
		{
			sem_wait(print);
			printf("%ld %zu died\n", now / 1000, philo->philo_id);
			sem_post(print);
			kill(-1, SIGINT);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->lock);
	}
	return (NULL);
}

pthread_t	start_monitor_thread(t_philo *philo, sem_t *print)
{
	pthread_t	thread;
	t_info		info;

	info.philo = philo;
	info.print = print;
	if (pthread_create(&thread, NULL, monitor_thread, &info) != 0)
	{
		kill(-1, SIGINT);
		write(STDERR_FILENO, "FAILED TO CREATE THREAD\n", 24);
		exit(EXIT_FAILURE);
	}
	return (thread);
}

char	*init_philo(t_philo *philo, t_condition condition, size_t philo_id)
{
	char	*sem_monitor;

	philo->philo_id = philo_id;
	philo->eat_count = 0;
	sem_monitor = gen_unique_sem_monitor(philo_id);
	philo->lock = sem_open(sem_monitor, O_CREAT | O_EXCL, 0644, 1);
	if (philo->lock == SEM_FAILED)
	{
		sem_close(philo->lock);
		sem_unlink(sem_monitor);
		kill(-1, SIGINT);
		write(STDERR_FILENO, "ERROR CREATING SEM_MONITOR\n", 26);
		exit(EXIT_FAILURE);
	}
	philo->ttd = get_cur_time() + condition.timetodie * 1000;
	return (sem_monitor);
}

void	*new_philo(size_t philo_id, t_condition condition, sem_t *forks, sem_t *print)
{
	t_philo	philo;
	char	*sem_monitor;

	sem_monitor = init_philo(&philo, condition, philo_id);
	exit(0);
	// start_monitor_thread(&philo, print);
	// while (1)
	// {
	// 	if (philo_eat(&philo, forks, condition, print) == -1)
	// 		break ;
	// 	if (philo_sleep(&philo, condition, print) == -1)
	// 		break ;
	// 	if (philo_think(&philo, print) == -1)
	// 		break ;
	// }
	(void)forks;
	(void)print;
	sem_close(philo.lock);
	sem_unlink(sem_monitor);
	return (NULL);
}
