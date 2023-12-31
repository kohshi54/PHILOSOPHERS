/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:38:56 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:38:56 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg_takefork(t_philo *philo, t_state *state)
{
	pthread_mutex_lock(&state->lock);
	if (state->alive == false)
	{
		pthread_mutex_unlock(&state->lock);
		return (-1);
	}
	printf("%ld %zu has taken a fork\n", get_cur_time(), philo->philo_id);
	pthread_mutex_unlock(&state->lock);
	return (0);
}

time_t	print_msg_eat(t_philo *philo, t_state *state)
{
	time_t	now;

	pthread_mutex_lock(&state->lock);
	if (state->alive == false)
	{
		pthread_mutex_unlock(&state->lock);
		return (-1);
	}
	now = get_cur_time();
	printf("%ld %zu is eating\n", now, philo->philo_id);
	pthread_mutex_unlock(&state->lock);
	return (now);
}

time_t	print_msg_sleep(t_philo *philo, t_state *state)
{
	time_t	now;

	pthread_mutex_lock(&state->lock);
	if (state->alive == false)
	{
		pthread_mutex_unlock(&state->lock);
		return (-1);
	}
	now = get_cur_time();
	printf("%ld %zu is sleeping\n", now, philo->philo_id);
	pthread_mutex_unlock(&state->lock);
	return (now);
}

int	print_msg_think(t_philo *philo, t_state *state)
{
	pthread_mutex_lock(&state->lock);
	if (state->alive == false)
	{
		pthread_mutex_unlock(&state->lock);
		return (-1);
	}
	printf("%ld %zu is thinking\n", get_cur_time(), philo->philo_id);
	pthread_mutex_unlock(&state->lock);
	return (0);
}
