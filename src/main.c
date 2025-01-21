#include "../philo.h"
#include <string.h>

void cleanup_arrays(t_philo **ps, pthread_t **th, t_info *i);

int main(int argc, char **argv)
{
	t_info  in;

	if (check_args(&in, argc, argv))
		return (1);
	init_dinner(&in);
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
    memset(threads_array, 0, in->ph_count);
	i = -1;
	while (++i < in->ph_count)
	{
		if (pthread_create(&threads_array[i], NULL, &routine, philos_array[i]) != 0)
			return (cleanup_all(philos_array, threads_array, in));
	}
	monitor(in->ph_count, philos_array, in);
	// i = -1;
	// while (++i < in->ph_count)
	// {
	// 	if (pthread_join(threads_array[i], NULL) != 0)
	// 		return (cleanup_all(philos_array, threads_array, in));
	// }
	cleanup_all(philos_array, threads_array, in);
}

void *routine(void *arg)
{
	t_philo *p;
	int     id;

	p = (t_philo *)arg;
	id = p->id;
	if (p->ph_count == 1)
		return(one_philo(p));
	while (!death_mutex(p->info, 0))
	{
		think(p, id);
		eat(p, id);
		sleeping(p, id);
		if (meals_mutex(p, NUM_EATEN) == p->num_meals)
		{
			p->full = 1;
			break ;
		}
	}
	return (arg);
}

void	assign_fork(t_philo *p)
{
	int	next;

	next = p->id - 2;
	if (next < 0)
		next = p->info->ph_count - 1;
	if ((p->id - 1) % 2 == 0 && (p->id - 1) != p->info->ph_count - 1)
	{
		p->fork = &p->info->forks[p->id - 1];
		p->otherfork = &p->info->forks[next];
	}
	else
	{
		p->fork = &p->info->forks[next];
		p->otherfork = &p->info->forks[p->id - 1];
	}
}

void	*one_philo(t_philo *p)
{
	pthread_mutex_lock(p->fork);
	print_msg(get_time(p->start), p, p->id, TAKEN_FORK);
	precise_usleep(p->time_hungry_max);
	pthread_mutex_unlock(p->fork);
	return (NULL);
}

void monitor(int num_philos, t_philo **ps, t_info *info)
{
	int i;
	long time_elapsed;

	while (!death_mutex(info, 0))
	{
		i = 0;
		while (i < num_philos)
		{
			time_elapsed = lmeal_mutex(ps[i], WHENWASIT);
			if (time_elapsed - 1 > (info->time_hungry_max / 1000))
			{
				if (ps[i]->full == 0)
				{
					death_mutex(info, 1);
					print_msg(get_time(ps[i]->info->start), ps[i], i + 1, DIED);
				}
				return ;
			}
			i++;
		}
	}
}

