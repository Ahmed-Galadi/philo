#include "philo.h"

void	*cstm_malloc(size_t bites)
{
	void	*output;

	output = malloc(bites);
	if (!output)
		error_exit(RED"ERROR !\nAllocation failed!");
	return (output);
}

void	handle_mutex(t_pmtx *mutex, t_opcode code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else 
		error_exit(RED"Wrong operation code for handle_mutex!"RESET)
}

