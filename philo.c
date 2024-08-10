
#include "philo.h"



int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		parse_input_data(&data, argv);
		data_init(&data);
		start_dining(&data);
		clean(&data);
	}
	else 
		error_exit(INP_ERR_MSG);
	return (0);
}
