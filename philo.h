/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:35:48 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/10 10:02:12 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

// Define color codes
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Define background colors
#define RED_BG      "\033[41m"
#define GREEN_BG    "\033[42m"
#define YELLOW_BG   "\033[43m"
#define BLUE_BG     "\033[44m"
#define MAGENTA_BG  "\033[45m"
#define CYAN_BG     "\033[46m"
#define WHITE_BG    "\033[47m"

// Define text attributes
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

#define	INP_ERR_MSG RED"Wrong Input:\n"\
RESET BOLD UNDERLINE"Please Enter:"\
RESET GREEN" ./philo 5 800 200 200 [5]"RESET

typedef	enum	e_opcode
{
	CREATE,
	DESTROY,
	INIT,
	JOIN,
	DETACH,
	LOCK,
	UNLOCK
}				t_opcode;

typedef pthread_mutex_t t_pmtx;
typedef struct s_data t_data;
// Fork
typedef struct	s_fork
{
	t_pmtx		fork;
	int			fork_id;
}				t_fork;

// Philosopher
typedef struct	s_philo
{
	int			philo_id;
	int			meals_count;
	bool		is_full;
	long		last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}				t_philo;

// Data Container
struct	s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	long	max_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

void	error_exit(const char *error_str);
void	parse_input_data(t_data **data, char **argv);
void	*cstm_malloc(size_t bites)

#endif
