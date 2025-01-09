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
	pthread_mutex_t eaten_mtx;
	long 			last_meal;
	struct timeval	lmeal_tval;
	pthread_mutex_t lmeal_mtx;
	pthread_mutex_t fork;
	int				dead;
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

t_info	*check_args(int argc, char **argv);
int		is_argv_digit(char *argv);
t_info	*init_info(int argc, char **argv);
int		ft_atoi(const char *n);
int		ft_isspace(int c);
int		death_mutex(t_info *info, int mode);
void	init_dinner(t_info *in);
void	print_msg(long time, t_philo *p, e_messages msg);
long	get_time(struct timeval since);
int		meals_mutex(t_philo *philo, int mode);
t_philo	**init_philos_array(t_info *in);
t_philo	*init_philo_struct(int i, t_info *info);
void	monitor(int num_philos, t_philo **ps, t_info *info);

#endif