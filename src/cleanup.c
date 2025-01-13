#include "../philo.h"

void    cleanup_info(t_info *in)
{
    int i;

    pthread_mutex_destroy(in->death_mutex);
    pthread_mutex_destroy(in->write_mutex);
    i = -1;
    while (++i < in->ph_count)
        pthread_mutex_destroy(&in->forks[i]);
    free (in->forks);
    free (in);
}

void    cleanup_philos_array(t_philo **ps, t_info *in)
{
    int i;

    i = -1;
    while (++i < in->ph_count)
    {
        pthread_mutex_destroy(ps[i]->eaten_mtx);
        pthread_mutex_destroy(ps[i]->lmeal_mtx);
        free(ps[i]);
    }
    free(ps);
}

void cleanup_all(t_philo **ps, pthread_t *th, t_info *in)
{
    int i;

    if (ps)
        cleanup_philos_array(ps, in);
    i = 0;
    if (th)
        free(th);
    cleanup_info(in);
}