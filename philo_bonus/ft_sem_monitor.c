/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:02:25 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/08/05 19:35:08 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

static size_t	count_digit(long n)
{
	size_t	count;

	count = 1;
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*head;

	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	head = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (head);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	count;

	count = count_digit(n);
	num = malloc(sizeof(char) * (count + 1));
	if (!num)
		return (NULL);
	num[count--] = '\0';
	while (n > 9)
	{
		num[count--] = (n % 10) + '0';
		n /= 10;
	}
	num[count] = (n % 10) + '0';
	return (num);
}

char	*gen_unique_sem_monitor(size_t philo_id)
{
	char	*sem_monitor;
	char	*tmp_philo_id;

	tmp_philo_id = ft_itoa(philo_id);
	if (tmp_philo_id == NULL)
	{
		kill(-1, SIGINT);
		exit(EXIT_FAILURE);
	}
	sem_monitor = ft_strjoin(SEM_MONITOR, tmp_philo_id);
	free(tmp_philo_id);	
	return (sem_monitor);
}
