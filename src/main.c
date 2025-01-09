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
	next = (p->id + 1) % p->info->ph_count;
	while (1)
	{
		if (death_mutex(p->info, 0) > 0)
			break;
		if (p->id % 2 == 0)
			usleep(100 * 1000);
		pthread_mutex_lock(&p->info->forks[next]);
		print_msg(get_time(p->info->start), p, TAKEN_FORK);
		pthread_mutex_lock(&p->info->forks[p->id]);
		print_msg(get_time(p->info->start), p, TAKEN_FORK);
		print_msg(get_time(p->info->start), p, IS_EATING);
		pthread_mutex_lock(&p->lmeal_mtx);
		p->last_meal = get_time(p->info->start);
		pthread_mutex_unlock(&p->lmeal_mtx);
		usleep(p->info->time_eating);
		pthread_mutex_unlock(&p->info->forks[next]);
		pthread_mutex_unlock(&p->info->forks[p->id]);
		print_msg(get_time(p->info->start), p, IS_SLEEPING);
		usleep(p->info->time_sleeping);
		print_msg(get_time(p->info->start), p, IS_THINKING);
		meals_mutex(p, 1); // p->meals ++;
		if (p->has_eaten == p->info->num_meals || death_mutex(p->info, 0) > 0)
			break;
	}
	return (NULL);
}

int	death_mutex(t_info *info, int mode)
{
	pthread_mutex_lock(info->death_mutex);
	if (mode == 0)
		return (info->dead);
	pthread_mutex_unlock(info->death_mutex);
	return (-1);
}

int meals_mutex(t_philo *philo, int mode)
{
	pthread_mutex_lock(&philo->eaten_mtx);
	if (mode == 0)
		return (philo->has_eaten);
	else if (mode == 1)
		philo->has_eaten ++;
	pthread_mutex_unlock(&philo->eaten_mtx);
	return (-1);
}

void	init_dinner(t_info *in)
{
	t_philo		**philos_array;
	pthread_t	**threads_array;
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
		if (pthread_create(threads_array[i], NULL, &routine, NULL) != 0)
			return ;
	}
	monitor(in->ph_count, philos_array, in);
	i = -1;
	while (++i < in->ph_count)
	{
		if (pthread_join(*threads_array[i], NULL) != 0)
			return;
	}
}

void monitor(int num_philos, t_philo **ps, t_info *info)
{
	int i;
	int time_elapsed;
	usleep(info->time_hungry_max);
	while (1)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_lock(&ps[i]->lmeal_mtx);
			time_elapsed = get_time(ps[i]->lmeal_tval);
			pthread_mutex_unlock(&ps[i]->lmeal_mtx);
			if (time_elapsed > info->time_hungry_max)
			{
				print_msg(get_time(ps[i]->info->start), ps[i], DIED);
				death_mutex(info, 1);
				return;
			}
			i++;
		}
		if (death_mutex(info, 0) > 0)
			break;
		usleep(1000 * 1000);
	}
}

