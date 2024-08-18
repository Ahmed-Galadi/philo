#include "philo.h"

void	print_state(t_philo *philo, t_state state, bool debug)
{
	long	time_passed;

	time_passed = get_time(MILISEC) - philo->data->start_simulation;
	handle_mutex(&philo->data->mutex_print, LOCK);
	if (debug)
		print_state_debug(state, philo, time_passed);
	else
	{
		if ((state == FORK1_TAKE || state == FORK2_TAKE) && !is_sim_end(philo->data))
			printf(WHITE"%-6ld"RESET" %d has taken a fork\n", time_passed, philo->philo_id);
	}
	handle_mutex(&philo->data->mutex_print, UNLOCK);
}
