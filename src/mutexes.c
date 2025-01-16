#include "../philo.h"

int	death_mutex(t_info *info, int mode)
{
	int	aux;

	aux = 0;
	if (pthread_mutex_lock(info->death_mutex) != 0)
		return (-1);
	if (mode == 0)
		aux = info->dead;
	if (mode == 1)
		info->dead = 1;
	if (pthread_mutex_unlock(info->death_mutex) != 0)
		return (-1);
	return (aux);
}

int meals_mutex(t_philo *philo, e_mealmtx mode)
{
	int	aux;

	aux = 0;
	if (pthread_mutex_lock(philo->eaten_mtx) != 0)
		return (-1);
	if (mode == NUM_EATEN)
		aux = philo->has_eaten;
	else if (mode == ATE_ONE)
		philo->has_eaten ++;
	pthread_mutex_unlock(philo->eaten_mtx);
	return (aux);
}


int	lmeal_mutex(t_philo *philo, e_lmealmtx mode)
{
	int	aux;

	aux = 0;
	if (pthread_mutex_lock(philo->lmeal_mtx) != 0)
		return (-1);
	if (mode == UPDATE)
		gettimeofday(&philo->lmeal_tval, NULL);
	else if (mode == WHENWASIT)
		aux = get_time(philo->lmeal_tval);
	if (pthread_mutex_unlock(philo->lmeal_mtx) != 0)
		return (-1);
	return (aux);
}
