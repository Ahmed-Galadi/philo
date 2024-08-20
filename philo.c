
#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		data = (t_data *)cstm_malloc(sizeof(t_data));
		parse_input_data(&data, argv);
		data_init(data);
		// start_dining(&data);
		// clean(&data);
		// printf("%ld %ld %ld %ld %ld", data->philo_nbr
		 // , data->time_to_die , data->time_to_eat, data->time_to_sleep, data->max_meals);
	}
	else 
		error_exit(INP_ERR_MSG);
	return (0);
}
