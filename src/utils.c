#include "../philo.h"

void print_msg(long time, t_philo *p, int id, e_messages msg)
{
	pthread_mutex_lock(p->info->write_mutex);
    if (!death_mutex(p->info, 0) && msg != DIED)
    {
        printf("%ld %d ", time, id);
        if (msg == TAKEN_FORK)
            printf("has taken a fork\n");
        else if (msg == IS_EATING)
            printf("is eating\n");
        else if (msg == IS_SLEEPING)
            printf("is sleeping\n");
        else if (msg == IS_THINKING)
            printf("is thinking\n");
    }
    else if (msg == DIED)
    {
        printf("%ld %d died\n", time, id);
    }
	pthread_mutex_unlock(p->info->write_mutex);
}

long	get_time(struct timeval since)
{
	struct timeval	now;
	long			time_elapsed;

	gettimeofday(&now, NULL);
	time_elapsed = (now.tv_sec - since.tv_sec) * 1000 + (now.tv_usec - since.tv_usec) / 1000;
	return (time_elapsed);
}

void	precise_usleep(long ms)
{
	struct timeval	stval;

	gettimeofday(&stval, NULL);
	while ((get_time(stval) * 1000) < ms)
		usleep(100);
}
