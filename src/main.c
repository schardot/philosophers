#include "../philo.h"

void cleanup_arrays(t_philo **ps, pthread_t **th, t_info *i);

int main(int argc, char **argv)
{
	t_info  *in;

	in = check_args(argc, argv);
	if (!in)
		return (1);
	init_dinner(in);
}

void init_dinner(t_info *in)
{
    t_philo **philos_array;
    pthread_t *threads_array;
    int i;

    philos_array = init_philos_array(in);
    if (!philos_array)
        return (cleanup_info(in));
    threads_array = malloc(in->ph_count * sizeof(pthread_t));
    if (!threads_array)
        return (cleanup_all(philos_array, NULL, in));
    i = -1;
    while (++i < in->ph_count)
    {
        if (pthread_create(&threads_array[i], NULL, &routine, philos_array[i]) != 0)
            return (cleanup_all(philos_array, threads_array, in));
    }
    monitor(in->ph_count, philos_array, in);
    i = -1;
    while (++i < in->ph_count)
    {
        if (pthread_join(threads_array[i], NULL) != 0)
            return (cleanup_all(philos_array, threads_array, in));
    }
}

void *routine(void *arg)
{
	t_philo *p;
    int     id;

	p = (t_philo *)arg;
    id = p->id;
    if (p->ph_count == 1)
		return(one_philo(p));
	if (id % 2 == 0)
        precise_usleep(p->time_eating / 2, p->start);
    while (1)
    {
		if (death_mutex(p->info, 0) > 0)
			break;
        eat(p, id);
        sleeping(p, id);
        think(p, id);
		if (p->has_eaten == p->info->num_meals)
        {
            p->full = 1;
            break ;
        }
	}
	return (NULL);
}

void	assign_fork(t_philo *p)
{
	int	next;

	next = (p->id) % p->ph_count;
	p->fork = &p->info->forks[p->id - 1];
	p->otherfork = &p->info->forks[next];
	if (p->id % 2 == 0)
	{
		p->otherfork = &p->info->forks[p->id - 1];
		p->fork = &p->info->forks[next];
	}
}

void	*one_philo(t_philo *p)
{
	pthread_mutex_lock(p->fork);
	print_msg(get_time(p->start), p, p->id, TAKEN_FORK);
    usleep(p->time_hungry_max);
    pthread_mutex_unlock(p->fork);
    return (NULL);
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
			pthread_mutex_lock(ps[i]->lmeal_mtx);
			time_elapsed = get_time(ps[i]->lmeal_tval);
			pthread_mutex_unlock(ps[i]->lmeal_mtx);
			if (time_elapsed > (info->time_hungry_max / 1000))
			{
                if (ps[i]->full == 0)
                {
                    pthread_mutex_lock(info->write_mutex);
                    printf("This is time elapsed: %ld and this is time hungry max: %ld\n", time_elapsed, (info->time_hungry_max / 1000));
                    pthread_mutex_unlock(info->write_mutex);
                    print_msg(get_time(ps[i]->info->start), ps[i], i + 1, DIED);
                }
                death_mutex(info, 1);
				return ;
			}
			i++;
        }
        precise_usleep(1000, ps[0]->start);
        if (death_mutex(info, 0) > 0)
			break;
	}
}

