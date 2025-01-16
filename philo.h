#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_info
{
	int		ph_count;
	long	time_hungry_max;
	long	time_eating;
	long	time_sleeping;
	long	num_meals;
	pthread_t *threads;
	pthread_mutex_t *forks;
	pthread_mutex_t *death_mutex;
	pthread_mutex_t *write_mutex;
	long start_time;
	struct timeval start;
	int dead;

} t_info;

typedef struct	s_philo
{
	int				id;
	int				is_eating;
	int				has_eaten;
    int             full;
	pthread_mutex_t	*eaten_mtx;
	struct timeval	lmeal_tval;
	pthread_mutex_t	*lmeal_mtx;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*otherfork;
	int				dead;
	int				ph_count;
	long			time_hungry_max;
	long			time_eating;
	long			time_sleeping;
	long			num_meals;
	struct timeval	start;
	t_info			*info;
}	t_philo;

typedef enum
{
	TAKEN_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DIED
} e_messages;

typedef enum
{
	NUM_EATEN,
	ATE_ONE,
} e_mealmtx;

typedef enum
{
	WHENWASIT,
	UPDATE
} e_lmealmtx;

t_info	*check_args(int argc, char **argv);
int		is_argv_digit(char *argv);
t_info	*init_info(int argc, char **argv);
int		ft_atoi(const char *n);
int		ft_isspace(int c);
int		death_mutex(t_info *info, int mode);
void	init_dinner(t_info *in);
void	print_msg(long time, t_philo *p, int id, e_messages msg);
long	get_time(struct timeval since);
t_philo	**init_philos_array(t_info *in);
t_philo	*init_philo_struct(int i, t_info *info);
void	*routine(void *arg);
void	monitor(int num_philos, t_philo **ps, t_info *info);
t_info	*init_info_mtxs(t_info *in);
void	*one_philo(t_philo *p);
void	assign_fork(t_philo *p);
t_philo	*init_philo_mtxs(t_philo *p);
void	eat(t_philo *p, int id);
void	sleeping(t_philo *p, int id);
void	think(t_philo *p, int id);
void	cleanup_info(t_info *in);
void	cleanup_philos_array(t_philo **ps, t_info *in);
void	cleanup_all(t_philo **ps, pthread_t *th, t_info *i);
// void    usleep(long duration_ms);
int		lmeal_mutex(t_philo *philo, e_lmealmtx mode);
int		meals_mutex(t_philo *philo, e_mealmtx mode);
void	precise_usleep(long ms);

#endif
