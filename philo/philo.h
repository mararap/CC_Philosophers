/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:14:34 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/03 16:59:21 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* structs and function prototypes */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_fork_lock;
typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct					s_philo
{
	int					id;
	pthread_t			tid;
	long long			last_meal_time;
	int					meal_count;
	t_fork_lock			*left;
	t_fork_lock			*right;
	t_dinner			*dinner;
};

struct					s_dinner
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			start_time;
	int					meals_required;
	t_philo				*philo_arr;
	t_fork_lock			*forks_arr;
	int					forks_init_count;
	int					is_dead;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
};

/* UTILS */

int						ph_atoui(const char *str);
long long				ph_get_time_ms(void);
void					ph_print_status(t_philo *philo, char *msg);

/* INIT */

int						ph_init_dinner(t_dinner *d);
int						ph_init_forks(t_dinner *d);
void					ph_init_philos(t_dinner *d);

/* THREADS */

int						ph_start_philo_threads(t_dinner *d);
int						ph_is_sim_over(t_dinner *d);

/* ACTIONS */

void					ph_take_forks(t_philo *p);
void					ph_eat(t_philo *p);
void					ph_drop_forks(t_philo *p);
void					ph_sleep(t_philo *p);
void					ph_think(t_philo *p);

/* MONITOR */

void					*ph_monitor(void *arg);

/* CLEANUP */

void					ph_free_arrays(t_dinner *d);
void					ph_destroy_mutexes(t_dinner *d, int stage);

#endif // !PHILO_H
