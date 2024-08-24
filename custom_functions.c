#include "philo.h"

void	*cstm_malloc(size_t bites)
{
	void	*output;

	output = malloc(bites);
	if (!output)
		error_exit(RED"ERROR !\nAllocation failed!");
	return (output);
}

static void	mutex_error_handle(int status, t_opcode code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK || code == DESTROY))
		error_exit(RED"ERROR!\nThe value specified by mutex is invalid!"RESET);
	else if (code == INIT && status == EINVAL)
		error_exit(RED"ERROR!\nThe value specified by attr is invalid!"RESET);
	else if (code == EDEADLK)
		error_exit("ERROR!\nA deadlock would occur if the thread blocked waiting for mutex!");
	else if (status == ENOMEM)
		error_exit(RED"ERROR!\nProcess can't allocate enough memo!"RESET);
	else if (status == EBUSY)
		error_exit(RED"ERROR!\nLocked Mutex!"RESET);
}

void	handle_mutex(t_pmtx *mutex, t_opcode code)
{
	if (code == LOCK)
		mutex_error_handle(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		mutex_error_handle(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_error_handle(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		mutex_error_handle(pthread_mutex_destroy(mutex), code);
	else 
		error_exit(RED"Wrong operation code for handle_mutex!"RESET);
}

static void thread_error_handler(int status, t_opcode code)
{
	(void)code;
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit(RED"ERROR!\nCan't create other thread, No resources"RESET);
	else if (status == EPERM)
		error_exit(RED"ERROR!\nCaller doesn't have permition!");
	else if (status == EINVAL && status == CREATE)
		error_exit(RED"ERROR!\nUnvalid attr!"RESET);
	else if (status == EINVAL && (status == JOIN || status == DETACH))
		error_exit(RED"ERROR!\nThread is not joinable!"RESET);
	else if (status == ESRCH)
		error_exit(RED"ERROR!No thread could be found!\n"RESET);
	else if (status == EDEADLK)
		error_exit(RED"ERROR!\nA deadlock was detected or the value of \
			 thread specifies the calling thread"RESET);
}

void	handle_thread(pthread_t *thread, void *(*f)(void *), void *data, t_opcode code)
{
	if (code == CREATE)
		thread_error_handler(pthread_create(thread, NULL, f, data), code);
	else if (code == JOIN)
		thread_error_handler(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		thread_error_handler(pthread_detach(*thread), code);
	else 
		error_exit(RED"ERROR!\nthread_handle: wrong code, use <CREATE>, <JOIN> or <DETACH>"RESET);
}






