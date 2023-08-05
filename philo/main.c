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
	if (set_vars(&condition, argc, argv, &state) == false)
		return (0);
	forks = create_forks(condition.numofphilo);
	if (forks == NULL)
		return (0);
	threads = malloc(sizeof(pthread_t *) * condition.numofphilo);
	if (threads == NULL)
		return (0);
	philo_array = generate_philosophers(condition, forks, &state);
	if (philo_array == NULL)
		return (0);
	monitor_philos(philo_array, condition, &state, argc);
	retrieve_philosophers(philo_array, condition);
	// printf("ending main\n");
	return (0);
}