#include "philo_bonus.h"

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

void	init_condition(t_condition *condition, int argc, char *argv[])
{
	condition->numofphilo = atoi(argv[1]);
	condition->timetodie = atoi(argv[2]);
	condition->timetoeat = atoi(argv[3]);
	condition->timetosleep  = atoi(argv[4]);
	if (argc == 6)
		condition->numtoeat = atoi(argv[5]);
}

bool	set_vars(t_condition *condition, int argc, char *argv[])
{
	init_condition(condition, argc, argv);
	return (true);
}