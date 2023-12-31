#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_condition	condition;
	sem_t		*forks;
	sem_t		*print;

	if (validate_input(argc, argv) == -1)
		return (0);
	if (set_vars(&condition, argc, argv) == false)
		return (0);
	forks = create_forks(condition.numofphilo);
	print = generate_philosophers(condition, forks);
	wait_for_philosophers(condition);
	cleanup_semaphore(forks, print);
	return (0);
}