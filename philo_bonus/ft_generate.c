#include "philo_bonus.h"

sem_t	*create_forks(size_t numofphilo)
{
	sem_t	*forks;

	forks = malloc(sizeof(sem_t));
	if (forks == NULL)
	{
		write(STDERR_FILENO, "ERROR ALLOCATING MEMORY\n", 24);
		exit(EXIT_FAILURE);
	}
	forks = sem_open(SEM_FORK, O_CREAT, 0644, numofphilo);
	if (forks == SEM_FAILED)
	{
		write(STDERR_FILENO, "ERROR CREATING SEM_FORK\n", 23);
		exit(EXIT_FAILURE);
	}
	return (forks);
}

void	generate_philosophers(t_condition condition, sem_t *forks)
{
	size_t		i;
	pid_t		pid;
	sem_t		*print;

	i = 0;
	print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (forks == SEM_FAILED)
	{
		write(STDERR_FILENO, "ERROR CREATING SEM_PRINT\n", 24);
		exit(EXIT_FAILURE);
	}
	while (i < condition.numofphilo)
	{
		pid = fork();
		if (pid < 0)
		{
			kill(-1, SIGINT);
			write(STDERR_FILENO, "FORK ERROR\n", 10);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			new_philo(i + 1, condition, forks, print);
			/*
			if ((i + 1) % 2 == 0)
				new_philo_even(i + 1, condition, forks, print);
			else
				new_philo_odd(i + 1, condition, forks);
			*/
		}
		i++;
	}
}