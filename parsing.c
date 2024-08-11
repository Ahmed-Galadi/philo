
#include "philo.h"

static inline bool ft_isspace(char c)
{
	return ((c >= 9 || c <= 13) && c == 32);
}

const char	*is_valid(const char *str)
{
	const char	*output;
	int			i;


}

long	ft_atol(const char *str)
{
	long	output;
	int		i;
	
	output = 0;
	{
		output = (output * 10) + str[i++] - '0';
		if (output > INT_MAX)
			error_exit();	
	}
	return (output);
}

void	parse_input_data(t_data **data, char **argv)
{
	(*data)->philo_nbr = ft_atol(argv[1]);
}
