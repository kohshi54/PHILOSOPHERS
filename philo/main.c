/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:40:49 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:41:04 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork **forks, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	free_philo_array(t_philo **philo_array, t_condition condition)
{
	size_t	i;

	i = 0;
	while (i < condition.numofphilo)
	{
		free(philo_array[i]);
		i++;
	}
	free(philo_array);
}

int	main(int argc, char *argv[])
{
	t_fork		**forks;
	t_condition	condition;
	t_state		state;
	t_philo		**philo_array;

	if (validate_input(argc, argv) == -1)
		return (0);
	if (set_vars(&condition, argc, argv, &state) == false)
		return (0);
	forks = create_forks(condition.numofphilo);
	if (forks == NULL)
		return (0);
	philo_array = generate_philosophers(condition, forks, &state);
	if (philo_array == NULL)
		return (0);
	monitor_philos(philo_array, condition, &state, argc);
	retrieve_philosophers(philo_array, condition);
	free_philo_array(philo_array, condition);
	free_forks(forks, condition);
	return (0);
}
