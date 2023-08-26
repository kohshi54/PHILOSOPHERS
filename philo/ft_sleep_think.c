/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep_think.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:39:07 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/26 15:39:19 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	if (print_msg_think(philo, state) == -1)
		return (-1);
	(void)forks;
	(void)condition;
	return (0);
}

int	philo_sleep(t_philo *philo, t_fork **forks, t_condition condition, t_state *state)
{
	time_t	now;

	now = print_msg_sleep(philo, state);
	if (now == -1)
		return (-1);
	wait_until(now + condition.timetosleep);
	(void)forks;
	return (now);
}
