#include "../philo.h"

void	eat(t_philo *p, int id)
{
	pthread_mutex_lock(p->fork);
	print_msg(get_time(p->start), p, id, TAKEN_FORK);
	// if (death_mutex(p->info, 0) > 0)
	// {
	// 	pthread_mutex_unlock(p->fork);
	// 	return ;
	// }
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
    print_msg(get_time(p->start), p, id, IS_SLEEPING);
    meals_mutex(p, 1);
    precise_usleep(p->time_sleeping);
}

void    check_full(t_info *in)
{
    int i;
    int full_philos;

    full_philos = 0;
    i = 0;
    while (i < in->ph_count)
    {
        if (meals_mutex(in->philos[i], NUM_EATEN) >= in->num_meals)
            full_philos++;
        i++;
    }
    if (full_philos == in->ph_count)
        death_mutex(in, 1);
}

void think(t_philo *p, int id)
{
	print_msg(get_time(p->start), p, id, IS_THINKING);
}
