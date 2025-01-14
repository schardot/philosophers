#include "../philo.h"

void print_msg(long time, t_philo *p, int id, e_messages msg)
{
	pthread_mutex_lock(p->info->write_mutex);
	printf("%ld %d ", time, id);
	if (msg == TAKEN_FORK)
		printf("has taken a fork\n");
	else if (msg == IS_EATING)
		printf("is eating\n");
	else if (msg == IS_SLEEPING)
		printf("is sleeping\n");
	else if (msg == IS_THINKING)
		printf("is thinking\n");
	else if (msg == DIED)
		printf("died\n");
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

// void usleep(long duration_ms)
// {
//     struct timeval current_time;
//     struct timeval now;
//     long elapsed_time;

//     gettimeofday(&now, NULL);
//     while (1)
//     {
//         gettimeofday(&current_time, NULL);
//         elapsed_time = (current_time.tv_sec - now.tv_sec) * 1000 + (current_time.tv_usec - now.tv_usec) / 1000;
//         if (elapsed_time >= duration_ms)
//             break;
//         usleep(100);
//     }
// }