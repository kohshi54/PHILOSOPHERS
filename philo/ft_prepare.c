#include "philo.h"

int	validate_input(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[3]) <= 0 || atoi(argv[4]) <= 0)
	{
		printf("parameters must be greater than zero\n");
		return (-1);
	}
	if (argc == 6 && atoi(argv[5]) <= 0)
	{
		printf("parameters must be greater than zero\n");
		return (-1);
	}
	return (0);
}

void	init_condition(t_condition *conditon, int argc, char *argv[])
{
	conditon->numofphilo = atoi(argv[1]);
	conditon->timetodie = atoi(argv[2]);
	conditon->timetoeat = atoi(argv[3]);
	conditon->timetosleep  = atoi(argv[4]);
	if (argc == 6)
		conditon->numtoeat = atoi(argv[5]);
}

bool	init_state(t_state *state)
{
	state->alive = 1;
	if (pthread_mutex_init(&(state->lock), NULL) != 0)
		return (false);
	return (true);
}