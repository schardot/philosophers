#include "../philo.h"

t_info *init_info(int argc, char **argv)
{
	t_info *in;

	in = NULL;
	in = (t_info *)malloc(sizeof(t_info));
	if (!in)
		return (NULL);
	if (!init_info_mtxs(in))
		return (NULL);
	in->ph_count = ft_atoi(argv[1]);
	in->time_hungry_max = ft_atoi(argv[2]) * 1000;
	in->time_eating = ft_atoi(argv[3]) * 1000;
	in->time_sleeping = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		in->num_meals = ft_atoi(argv[5]);
	gettimeofday(&in->start, NULL);
	in->start_time = get_time(in->start);
	in->dead = 0;
	return (in);
}

t_philo **init_philos_array(t_info *in)
{
	t_philo **philos_array;
	int i;

	philos_array = malloc(in->ph_count * sizeof(t_philo *));
	if (!philos_array)
		return (NULL);
	i = -1;
	while (++i < in->ph_count)
	{
		philos_array[i] = init_philo_struct(i, in);
		if (!philos_array[i])
			return (NULL); // cleanup better afterwards
		assign_fork(philos_array[i]);
	}
	return (philos_array);
}

t_philo *init_philo_struct(int i, t_info *info)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->is_eating = 0;
	philo->has_eaten = 0;
	philo->dead = 0;
	philo->ph_count = info->ph_count;
	philo->time_hungry_max = info->time_hungry_max;
	philo->time_eating = info->time_eating;
	philo->time_sleeping = info->time_sleeping;
	philo->num_meals = info->num_meals;
	philo->start = info->start;
	philo->info = info;
	philo->lmeal_tval = info->start;
	init_philo_mtxs(philo);
	return (philo);
}

t_philo	*init_philo_mtxs(t_philo *p)
{
	p->eaten_mtx = malloc(sizeof(pthread_mutex_t));
	p->lmeal_mtx = malloc(sizeof(pthread_mutex_t));
	if (!p->eaten_mtx || !p->lmeal_mtx)
		return (NULL);
	pthread_mutex_init(p->eaten_mtx, NULL);
	pthread_mutex_init(p->lmeal_mtx, NULL);
	return (p);
}

t_info	*init_info_mtxs(t_info *in)
{
	int	i;

	i = -1;
	in->death_mutex = malloc(sizeof(pthread_mutex_t));
	in->write_mutex = malloc(sizeof(pthread_mutex_t));
	in->forks = malloc(in->ph_count * sizeof(pthread_mutex_t));
	if (!in->death_mutex || !in->write_mutex || !in->forks)
		return (NULL);
	pthread_mutex_init(in->death_mutex, NULL);
	pthread_mutex_init(in->write_mutex, NULL);
	while (++i < in->ph_count)
	{
		pthread_mutex_init(&in->forks[i], NULL);
	}
	return (in);
	}
