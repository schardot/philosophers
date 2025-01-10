#include "../philo.h"

int	death_mutex(t_info *info, int mode)
{
	int	value;

	value = -1;
	pthread_mutex_lock(info->death_mutex);
	if (mode == 0)
		value = info->dead;
	pthread_mutex_unlock(info->death_mutex);
	return (value);
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


