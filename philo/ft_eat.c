#include "philo.h"

int	philo_eat_even(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t	now;

	pthread_mutex_lock(&(forks[philo->philo_id - 1]->lock));
	if (print_msg_takefork(philo, state) == -1)
	{
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		return (-1);
	}
	pthread_mutex_lock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	if (print_msg_takefork(philo, state) == -1)
	{
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		return (-1);	
	}
	now = 0;
	if (print_msg_eat(philo, state, &now) == -1)
	{
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		return (-1);
	}
	pthread_mutex_lock(&(philo->lock));
	philo->ttd = now + condition.timetodie * 1000;
	pthread_mutex_unlock(&(philo->lock));
	wait_until(now + condition.timetoeat * 1000);
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	// printf("%zu has put down a fork\n", philo->philo_id);
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	// printf("%zu has put down a fork\n", philo->philo_id);
	pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
	return (0);
}

int	philo_eat_odd(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t	now;

	if (philo->philo_id == 1 && condition.numofphilo == 1)
		return (-1);
	pthread_mutex_lock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	if (print_msg_takefork(philo, state) == -1)
	{
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		return (-1);
	}
	pthread_mutex_lock(&(forks[philo->philo_id - 1]->lock));
	if (print_msg_takefork(philo, state) == -1)
	{
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		return (-1);
	}
	now = 0;
	if (print_msg_eat(philo, state, &now) == -1)
	{
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		return (-1);
	}
	pthread_mutex_lock(&philo->lock);
	philo->ttd = now + condition.timetodie * 1000;
	pthread_mutex_unlock(&philo->lock);
	wait_until(now + condition.timetoeat * 1000);
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	// printf("%zu has put down a fork\n", philo->philo_id);
	pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
	// printf("%zu has put down a fork\n", philo->philo_id);
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	return (0);
}