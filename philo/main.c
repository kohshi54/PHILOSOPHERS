#include "philo.h"

int	main(int argc, char *argv[])
{
	t_fork		**forks;
	t_condition	condition;
	t_state		state;
	pthread_t	**threads;
	t_philo		**philo_array;

	if (validate_input(argc, argv) == -1)
		return (0);
	init_condition(&condition, argc, argv);
	init_state(&state);
	forks = create_forks(condition.numofphilo);
	threads = malloc(sizeof(pthread_t *) * condition.numofphilo);
	philo_array = generate_philosophers(threads, condition, forks, &state);
	monitor_philos(philo_array, condition, &state, argc);
	retrieve_philosophers(threads, condition);
	// printf("ending main\n");
	return (0);
}