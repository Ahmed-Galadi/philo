#include "philo.h"

void	print_state_debug(t_philo *philo, t_state state, long time_passed)
{
	if (state == FORK1_TAKE&& !is_sim_end(philo->data))
		printf(WHITE"%6ld]]"RESET" %d has taken first fork [%d]\n", time_passed, philo->philo_id, philo->fork_1->fork_id);
	else if (state == FORK2_TAKE&& !is_sim_end(philo->data))
		printf(WHITE"%6ld"RESET" %d has taken second fork [%d]\n", time_passed, philo->philo_id, philo->fork_2->fork_id);
	else if (state == EATING && !is_sim_end(philo->data))	
		printf(WHITE"%6ld"RESET" %d is eating\tmeals[%d]\n", time_passed, philo->philo_id, philo->meals_count);
	else if (state == THINKING && !is_sim_end(philo->data))	
		printf(WHITE"%6ld"RESET" %d is thinking\n", time_passed, philo->philo_id);
	else if (state == SLEEPING && !is_sim_end(philo->data))	
		printf(WHITE"%6ld"RESET" %d is sleeping\n", time_passed, philo->philo_id);
	else if (state == DEATH)	
		printf(RED"%6ld"RESET" %d is dead\n", time_passed, philo->philo_id);
}

void	print_state(t_philo *philo, t_state state, bool debug)
{
	long	time_passed;

	time_passed = get_time(MILISEC) - philo->data->start_simulation;
	if (philo->is_full)
		return ;
	handle_mutex(&philo->data->mutex_print, LOCK);
	if (debug)
		print_state_debug(philo, state, time_passed);
	else
	{
		if ((state == FORK1_TAKE || state == FORK2_TAKE) && !is_sim_end(philo->data))
			printf(WHITE"%ld"RESET" %d has taken a fork\n", time_passed, philo->philo_id);
		else if (state == EATING && !is_sim_end(philo->data))	
			printf(GREEN"%ld %d is eating\n"RESET, time_passed, philo->philo_id);
		else if (state == THINKING && !is_sim_end(philo->data))	
			printf(WHITE"%ld"RESET" %d is thinking\n", time_passed, philo->philo_id);
		else if (state == SLEEPING && !is_sim_end(philo->data))	
			printf(WHITE"%ld"RESET" %d is sleeping\n", time_passed, philo->philo_id);
		else if (state == DEATH)	
			printf(RED"%ld %d is dead\n"RESET, time_passed, philo->philo_id);
	}
	handle_mutex(&philo->data->mutex_print, UNLOCK);
}
