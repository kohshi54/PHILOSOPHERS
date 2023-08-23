#include "philo.h"

time_t	get_cur_time()
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000 + cur.tv_usec / 1000);
}

void	wait_until(time_t until)
{
	time_t	cur_time_in_milisecond;

	while (1)
	{
		cur_time_in_milisecond = get_cur_time();
		if (until <= cur_time_in_milisecond)
			break ;
	}
}