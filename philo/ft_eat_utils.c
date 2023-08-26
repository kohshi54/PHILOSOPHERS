/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:07:47 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 16:07:48 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_ttd(t_philo *philo, time_t now, t_condition condition)
{
	pthread_mutex_lock(&philo->lock);
	philo->ttd = now + condition.timetodie;
	pthread_mutex_unlock(&philo->lock);
}

void	add_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
}

int	unlock_mutex_when_error_even(int rule, t_fork **forks, t_philo *philo)
{
	if (rule == 1)
		pthread_mutex_unlock(&forks[philo->right_fork_id]->lock);
	if (rule == 2)
	{
		pthread_mutex_unlock(&forks[philo->left_fork_id]->lock);
		pthread_mutex_unlock(&forks[philo->right_fork_id]->lock);
	}
	return (-1);
}

int	unlock_mutex_when_error_odd(int rule, t_fork **forks, t_philo *philo)
{
	if (rule == 1)
		pthread_mutex_unlock(&forks[philo->left_fork_id]->lock);
	if (rule == 2)
	{
		pthread_mutex_unlock(&forks[philo->right_fork_id]->lock);
		pthread_mutex_unlock(&forks[philo->left_fork_id]->lock);
	}
	return (-1);
}
