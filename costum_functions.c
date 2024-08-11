#include "philo.h"

void	*cstm_malloc(size_t bites)
{
	void	*output;

	output = malloc(bites);
	if (!output)
		error_exit(RED"ERROR !\nAllocation failed!");
	return (output);
}
