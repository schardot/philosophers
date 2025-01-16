#include "../philo.h"

void	eat(t_philo *p, int id)
{
	pthread_mutex_lock(p->fork);
	print_msg(get_time(p->start), p, id, TAKEN_FORK);
	if (death_mutex(p->info, 0) > 0)
	{
		pthread_mutex_unlock(p->fork);
		return ;
	}
	pthread_mutex_lock(p->otherfork);
	print_msg(get_time(p->start), p, id, TAKEN_FORK);
	print_msg(get_time(p->start), p, id, IS_EATING);
	lmeal_mutex(p, UPDATE);
	precise_usleep(p->time_eating);
	pthread_mutex_unlock(p->otherfork);
	pthread_mutex_unlock(p->fork);
}

void	sleeping(t_philo *p, int id)
{
	if (death_mutex(p->info, 0) > 0)
	{
		pthread_mutex_unlock(p->fork);
		return ;
	}
	print_msg(get_time(p->start), p, id, IS_SLEEPING);
	precise_usleep(p->time_sleeping);
}

void think(t_philo *p, int id)
{
	long t_eat;
	long t_sleep;
	long t_think;

	if (death_mutex(p->info, 0) > 0)
	{
		pthread_mutex_unlock(p->fork);
		return ;
	}
	print_msg(get_time(p->start), p, id, IS_THINKING);
	t_eat = p->info->time_eating;
	t_sleep = p->info->time_sleeping;
	//t_think = t_eat * 2 - t_sleep;
	t_think = 10000;
	if (t_think < 0)
		t_think = 0;
	// usleep(t_think);
	meals_mutex(p, 1);
}
