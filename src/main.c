#include "../philo.h"

int main(int argc, char **argv)
{
	t_info  *in;

	in = check_args(argc, argv);
	if (!in)
		return (1);
	init_dinner(in);

}

void *routine(void *arg)
{
	t_philo *p;
	int next;

	p = (t_philo *)arg;
	if (p->ph_count == 1)
		return(one_philo(p));
	next = (p->id) % p->ph_count;
	if (p->id % 2 == 0)
			usleep(1000);
	while (1)
	{
		if (death_mutex(p->info, 0) > 0)
			break;

		print_msg(get_time(p->start), p, IS_EATING);
		pthread_mutex_lock(&p->lmeal_mtx);
		p->last_meal = get_time(p->start);
		pthread_mutex_unlock(&p->lmeal_mtx);
		usleep(p->time_eating);
		pthread_mutex_unlock(&p->info->forks[next]);
		pthread_mutex_unlock(&p->info->forks[p->id - 1]);
		print_msg(get_time(p->start), p, IS_SLEEPING);
		usleep(p->time_sleeping);
		print_msg(get_time(p->start), p, IS_THINKING);
		usleep(p->time_hungry_max/3);
		meals_mutex(p, 1);
		if (p->has_eaten == p->info->num_meals || death_mutex(p->info, 0) > 0)
			break;
	}
	return (NULL);
}

void	assign_fork(t_philo *p)
{
	int	next;

	next = (p->id) % p->ph_count;
	p->fork = p->info->forks[p->id - 1];
	p->otherfork = &p->info->forks[next];
	if (p->id % 2 == 0)
	{
		p->otherfork = &p->info->forks[p->id - 1];
		p->fork = p->info->forks[next];
	}
}

void	*one_philo(t_philo *p)
{
	pthread_mutex_lock(&p->info->forks[p->id - 1]);
	print_msg(get_time(p->start), p, TAKEN_FORK);
	usleep(p->time_hungry_max);
	return (NULL);
}

void	init_dinner(t_info *in)
{
	t_philo		**philos_array;
	pthread_t	*threads_array;
	int			i;

	philos_array = init_philos_array(in);
	if (!philos_array)
		return ;
	threads_array = malloc(in->ph_count * sizeof(pthread_t));
	if (!threads_array)
		return ; //cleanuppppp
	i = -1;
	while (++i < in->ph_count)
	{
		if (pthread_create(&threads_array[i], NULL, &routine, philos_array[i]) != 0)
			return ;
	}
	monitor(in->ph_count, philos_array, in);
	i = -1;
	while (++i < in->ph_count)
	{
		if (pthread_join(threads_array[i], NULL) != 0)
			return;
	}
}

void monitor(int num_philos, t_philo **ps, t_info *info)
{
	int i;
	long time_elapsed;
    usleep(1000);
    while (1)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_lock(&ps[i]->lmeal_mtx);
			time_elapsed = get_time(ps[i]->lmeal_tval);
			pthread_mutex_unlock(&ps[i]->lmeal_mtx);
			if (time_elapsed > (info->time_hungry_max / 1000))
			{
				print_msg(get_time(ps[i]->info->start), ps[i], DIED);
				death_mutex(info, 1);
				return;
			}
			i++;
        }
        usleep(1000);
        if (death_mutex(info, 0) > 0)
			break;
	}
}

