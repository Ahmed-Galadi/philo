
#include "philo.h"



int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		get_input_data(&data, argv);
		data_init(&data);

	}
	else 
		error_exit(INP_ERR_MSG);
	return (0);
}
