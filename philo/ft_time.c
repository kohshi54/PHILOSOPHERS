#include "philo.h"

time_t	get_cur_time()
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (cur.tv_sec * 1000000) + cur.tv_usec;
}

void	wait_until(time_t until)
{
	struct timeval	cur;
	time_t			current_time_in_microseconds;

	while (1)
	{
		// printf("until: %ld\n", until);
		gettimeofday(&cur, NULL);
		current_time_in_microseconds = (cur.tv_sec * 1000000) + cur.tv_usec;
		// printf("%ld\n", current_time_in_microseconds);
		if (until <= current_time_in_microseconds)
			break ;
		// printf("eating...\n");
	}
}