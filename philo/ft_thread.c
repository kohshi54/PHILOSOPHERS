/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:39:27 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:40:05 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*new_philo_even(void *arg)
{
	t_info	*info;

	info = arg;
	pthread_mutex_lock(&info->philo->lock);
	info->philo->ttd = get_cur_time() + info->condition.timetodie;
	pthread_mutex_unlock(&info->philo->lock);
	while (1)
	{
		if (philo_eat_even(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_sleep(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_think(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
	}
	free(info);
	return (NULL);
}

void	*new_philo_odd(void *arg)
{
	t_info	*info;

	info = arg;
	pthread_mutex_lock(&info->philo->lock);
	info->philo->ttd = get_cur_time() + info->condition.timetodie;
	pthread_mutex_unlock(&info->philo->lock);
	while (1)
	{
		if (philo_eat_odd(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_sleep(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
		if (philo_think(info->philo, info->forks, info->condition, info->state) == -1)
			break ;
	}
	free(info);
	return (NULL);
}
