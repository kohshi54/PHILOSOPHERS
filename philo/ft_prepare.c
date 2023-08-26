/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:38:15 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:38:45 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		printf("parameters must be greater than zero\n");
		return (-1);
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
	{
		printf("parameters must be greater than zero\n");
		return (-1);
	}
	return (0);
}

void	init_condition(t_condition *condition, int argc, char *argv[])
{
	condition->numofphilo = ft_atoi(argv[1]);
	condition->timetodie = ft_atoi(argv[2]);
	condition->timetoeat = ft_atoi(argv[3]);
	condition->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		condition->numtoeat = ft_atoi(argv[5]);
}

bool	init_state(t_state *state)
{
	state->alive = 1;
	if (pthread_mutex_init(&(state->lock), NULL) != 0)
		return (false);
	return (true);
}

bool	set_vars(t_condition *condition, int argc, char *argv[], t_state *state)
{
	init_condition(condition, argc, argv);
	if (init_state(state) == false)
		return (false);
	return (true);
}
