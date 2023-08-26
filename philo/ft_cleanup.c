/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:26:32 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:26:40 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo **philo_array, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(philo_array[i]);
		i++;
	}
	free(philo_array);
}

void	free_infos(t_info **info_array, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(info_array[i]);
		i++;
	}
	free(info_array);
}

void	*free_forks_and_return_null(t_fork **forks, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}

void	retrieve_philosophers(t_philo **philo_array, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		pthread_join(philo_array[i]->thread_id, NULL);
		i++;
	}
}
