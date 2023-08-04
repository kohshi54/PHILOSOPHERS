#include "philo_bonus.h"

void	set_ttd(t_philo *philo, time_t now, t_condition condition)
{
	sem_wait(philo->lock);
	philo->ttd = now + condition.timetodie * 1000;
	sem_post(philo->lock);
}

void	add_eat_count(t_philo *philo)
{
	sem_wait(philo->lock);
	philo->eat_count++;
	sem_post(philo->lock);
}

int	philo_eat(t_philo *philo, sem_t *forks, t_condition condition, sem_t *print)
{
	time_t	now;

	sem_wait(forks);
	print_msg_takefork(philo, print);
	sem_wait(forks);
	print_msg_takefork(philo, print);
	now = print_msg_eat(philo, print);
	set_ttd(philo, now, condition);
	wait_until(now + condition.timetoeat * 1000);
	add_eat_count(philo);
	sem_post(forks);
	sem_post(forks);
	return (0);
}
