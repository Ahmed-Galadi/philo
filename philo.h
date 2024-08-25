/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:35:48 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/25 17:56:00 by agaladi          ###   ########.fr       */
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

// [eat, sleep, think] messages
#define FORK_MSG BOLD"%ld "BLUE_BG"%d"RESET" "BLUE BOLD"\
has taken a fork ‎𐂐\n"RESET
#define EATING_MSG BOLD UNDERLINE"%ld "RESET BOLD GREEN_BG"\
%d"RESET" "GREEN BOLD UNDERLINE"is eating ‎𐂐◯𓇋(๑ᵔ⤙ᵔ๑)\n"RESET
#define SLEEPING_MSG BOLD"%ld "MAGENTA_BG"%d"RESET" "MAGENTA BOLD"\
is sleeping ꒰ ꒡⌓꒡꒱zzz\n"RESET
#define THINKING_MSG BOLD"%ld "YELLOW_BG"%d"RESET"\
 "YELLOW BOLD"is thinking (≖_≖ )?\n"RESET
#define DEATH_MSG UNDERLINE"%ld "RESET BOLD RED_BG"\
%d"RESET" "RED BOLD UNDERLINE"is dead "RESET BOLD RED"(×_×)\n"RESET

#define	INP_ERR_MSG RED"Wrong Input:\n"\
RESET BOLD UNDERLINE"Please Enter:"\
RESET GREEN" ./philo <philo_nbr> <time_to_die> <time_to_eat> <time_to_sleep> [meals]"RESET
#define	DEBUG 0

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

typedef enum	e_time
{
	MICROSEC,
	MILISEC,
	SEC,
}				t_time;

typedef pthread_mutex_t t_pmtx;
typedef struct s_data t_data;
// Fork
typedef struct	s_fork
{
	t_pmtx		fork;
	int			fork_id;
}				t_fork;
// philosophers state
typedef enum e_state
{
	SLEEPING,
	EATING,
	THINKING,
	FORK1_TAKE,
	FORK2_TAKE,
	DEATH,
}			t_state;
// Philosopher
typedef struct	s_philo
{
	int			philo_id;
	int			meals_count;
	bool		is_full;
	long		last_meal;
	t_fork		*fork_1;
	t_fork		*fork_2;
	pthread_t	thread_id;
	t_pmtx		philo_mutex;
	t_data		*data;
}				t_philo;

// Data Container
struct	s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		max_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		is_threads_ready;
	pthread_t	monitor_thread;
	long		running_threads_count;
	t_pmtx		mutex_table;
	t_pmtx		mutex_print;
	t_fork		*forks;
	t_philo		*philos;
};
// error handler
void	error_exit(const char *error_str);
// input parse
void	parse_input_data(t_data **data, char **argv);
// costum functions
void	*cstm_malloc(size_t bites);
void	data_init(t_data *data);
void	handle_thread(pthread_t *thread, void *(*f)(void *), void *data, t_opcode code);
void	handle_mutex(t_pmtx *mutex, t_opcode code);
bool	is_sim_end(t_data *data);
bool	get_bool_mutex(t_pmtx *mutex, bool *to_get);
void	set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val);
void	set_long_mutex(t_pmtx *mutex, long *to_set, long val);
long	get_long_mutex(t_pmtx *mutex, long *to_get);
void	set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val);
long	get_time(t_time time_code);
void	wait_threads(t_data *data);
void	accurate_usleep(long usecond, t_data *data);
void	print_state(t_philo *philo, t_state state, bool debug);
void	start_dining(t_data *data);
bool	is_allthreads_runing(t_pmtx *mutex, long *threads, long philo_nbr);
void	long_pp(t_pmtx *mutex, long *count);
void	*monitoring(void *data);

#endif
