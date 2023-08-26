/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:36:51 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 16:09:46 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_all_philo_has_eaten_at_least_counttoeat(t_philo **philo_array, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_mutex_lock(&(philo_array[i]->lock));
		if (philo_array[i]->eat_count < condition.numtoeat)
		{
			pthread_mutex_unlock(&philo_array[i]->lock);
			return (false);
		}
		pthread_mutex_unlock(&philo_array[i]->lock);
		i++;
	}
	return (true);
}

int	check_death(t_philo **philo_array, t_condition condition, t_state *state)
{
	size_t	i;
	time_t	now;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_mutex_lock(&(philo_array[i]->lock));
		now = get_cur_time();
		if (philo_array[i]->ttd < now && philo_array[i]->ttd != 0)
		{
			pthread_mutex_lock(&state->lock);
			state->alive = false;
			pthread_mutex_unlock(&state->lock);
			printf("%ld %zu died\n", now, philo_array[i]->philo_id);
			pthread_mutex_unlock(&philo_array[i]->lock);
			return (-1);
		}
		pthread_mutex_unlock(&philo_array[i]->lock);
		i++;
	}
	return (0);
}

int	check_eatcount(t_philo **philo_array, t_condition condition, t_state *state)
{
	if (check_all_philo_has_eaten_at_least_counttoeat(philo_array, condition) == true)
	{
		pthread_mutex_lock(&state->lock);
		state->alive = false;
		pthread_mutex_unlock(&state->lock);
		return (-1);
	}
	return (0);
}

void	monitor_philos(t_philo **philo_array, t_condition condition, t_state *state, int argc)
{
	while (1)
	{
		if (check_death(philo_array, condition, state) == -1)
			return ;
		if (argc == 6)
			if (check_eatcount(philo_array, condition, state) == -1)
				return ;
	}
}
