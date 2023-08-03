#include "philo.h"

void	set_ttd(t_philo *philo, time_t now, t_condition condition)
{
	pthread_mutex_lock(&(philo->lock));
	philo->ttd = now + condition.timetodie * 1000;
	pthread_mutex_unlock(&(philo->lock));
}

void	add_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
}

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
	now = print_msg_eat(philo, state);
	if (now == -1)
	{
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		return (-1);
	}
	set_ttd(philo, now, condition);
	wait_until(now + condition.timetoeat * 1000);
	add_eat_count(philo);
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
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
	now = print_msg_eat(philo, state);
	if (now == -1)
	{
		pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
		pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
		return (-1);
	}
	set_ttd(philo, now, condition);
	wait_until(now + condition.timetoeat * 1000);
	add_eat_count(philo);
	pthread_mutex_unlock(&(forks[(philo->philo_id - 1)]->lock));
	pthread_mutex_unlock(&(forks[philo->philo_id == condition.numofphilo ? 0 : philo->philo_id]->lock));
	return (0);
}