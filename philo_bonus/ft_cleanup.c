#include "philo_bonus.h"

void	wait_for_philosophers(t_condition condition)
{
	int		status;

	while (waitpid(-1, &status, 0) > 0)
	{

	}
	(void)condition;
}

void	cleanup_semaphore(sem_t *fork, sem_t *print)
{
	sem_close(fork);
	sem_unlink(SEM_FORK);
	sem_close(print);
	sem_unlink(SEM_PRINT);
}