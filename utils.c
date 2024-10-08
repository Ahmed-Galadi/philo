/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:41:50 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/26 23:42:20 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_data *data)
{
	while (!get_bool_mutex(&data->mutex_table, &data->is_threads_ready))
		;
}

bool	is_sim_end(t_data *data)
{
	return (get_bool_mutex(&data->mutex_table, &data->end_simulation));
}

long	get_time(t_time time_code)
{
	struct timeval	time_val;

	if (gettimeofday(&time_val, NULL))
		error_exit(RED"ERROR!\ngettimeofday failuer."RESET);
	if (time_code == SEC)
		return (time_val.tv_sec + (time_val.tv_usec / 1e6));
	else if (time_code == MILISEC)
		return ((time_val.tv_sec * 1e3) + (time_val.tv_usec / 1e3));
	else if (time_code == MICROSEC)
		return ((time_val.tv_sec * 1e6) + time_val.tv_usec);
	else
		error_exit(RED"ERROR!\nerror in \'get_time()\' input"RESET);
	return (666);
}

void	accurate_usleep(long usecond, t_data *data)
{
	long	start;
	long	passed;
	long	left;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usecond)
	{
		if (is_sim_end(data))
			break ;
		passed = get_time(MICROSEC) - start;
		left = usecond - passed;
		if (left > 1e3)
			usleep(200);
		else
		{
			while (get_time(MICROSEC) - start < usecond)
				;
		}
	}
}

void	error_exit(const char *error_str)
{
	printf("%s\n", error_str);
	exit(EXIT_FAILURE);
}
