#include "../philo.h"

void	eat(t_philo *p, int id)
{
	pthread_mutex_lock(p->fork);
	print_msg(get_time(p->start), p, id, TAKEN_FORK);
	pthread_mutex_lock(p->otherfork);
	print_msg(get_time(p->start), p, id, TAKEN_FORK);
	print_msg(get_time(p->start), p, id, IS_EATING);
	pthread_mutex_lock(p->lmeal_mtx);
	gettimeofday(&p->lmeal_tval, NULL);
	pthread_mutex_unlock(p->lmeal_mtx);
	usleep(p->time_eating);
	pthread_mutex_unlock(p->otherfork);
	pthread_mutex_unlock(p->fork);
}

void	sleeping(t_philo *p, int id)
{
	print_msg(get_time(p->start), p, id, IS_SLEEPING);
	usleep(p->time_sleeping);
}

void think(t_philo *p, int id)
{
	print_msg(get_time(p->start), p, id, IS_THINKING);
	usleep(p->time_hungry_max / 2);
	meals_mutex(p, 1);
}