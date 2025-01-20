#include "../philo.h"

void cleanup_info(t_info *in)
{
	int i;

	if (in->death_mutex)
	{
		pthread_mutex_destroy(in->death_mutex);
		free(in->death_mutex);
		in->death_mutex = NULL;
	}
	if (in->write_mutex)
	{
		pthread_mutex_destroy(in->write_mutex);
		free(in->write_mutex);
		in->write_mutex = NULL;
	}
	if (in->forks)
	{
		i = -1;
		while (++i < in->ph_count)
			pthread_mutex_destroy(&in->forks[i]);
		free(in->forks);
		in->forks = NULL;
	}
}

void cleanup_philos_array(t_philo **ps, t_info *in)
{
    int i;

    if (!ps || !in)
        return;
    i = -1;
    while (++i < in->ph_count)
    {
        if (ps[i])
        {
            if (ps[i]->eaten_mtx)
            {
                pthread_mutex_destroy(ps[i]->eaten_mtx);
                free(ps[i]->eaten_mtx);
                ps[i]->eaten_mtx = NULL;
            }
            if (ps[i]->lmeal_mtx)
            {
                pthread_mutex_destroy(ps[i]->lmeal_mtx);
                free(ps[i]->lmeal_mtx);
                ps[i]->lmeal_mtx = NULL;
            }
            free(ps[i]);
            ps[i] = NULL;
        }
    }
    free(ps);
    ps = NULL;
}

void cleanup_all(t_philo **ps, pthread_t *th, t_info *in)
{
	if (th)
	{
		int i = -1;
		while (++i < in->ph_count)
		{
			pthread_join(th[i], NULL);
		}
		free(th);
	}
	if (ps)
		cleanup_philos_array(ps, in);
	cleanup_info(in);
}
