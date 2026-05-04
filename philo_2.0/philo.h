/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 13:29:44 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/04 14:56:56 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef pthread_mutex_t	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct s_philo
{
	int				id;
	pthread_t		tid;
	long long		last_meal;
	long long		meal_count;
	t_fork			*left;
	t_fork			*right;
	t_dinner		*dinner;
};

struct s_dinner
{
	int				philo_count;
	long long		ttd;
	long long		tte;
	long long		tts;
	long long		start_time;
	int				meals_required;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	done_lock;
	pthread_mutex_t	meal_lock;
	int				is_done;
	int				forks_init;
};

/* utils.c */
long long			ph_atoull(const char *str);
long long			ph_get_time_us(void);
void				ph_print(t_philo *p, const char *msg);
void				ph_wait_us(long long us, t_dinner *d);

/* init.c */
int					ph_init_dinner(t_dinner *d);
int					ph_init_forks(t_dinner *d);
void				ph_init_philos(t_dinner *d);

/* threads.c */
int					ph_start_threads(t_dinner *d);
int					ph_is_done(t_dinner *d);

/* actions.c */
void				ph_take_forks(t_philo *p);
void				ph_eat(t_philo *p);
void				ph_drop_forks(t_philo *p);
void				ph_sleep(t_philo *p);
void				ph_think(t_philo *p);

/* monitor.c */
void				*ph_monitor(void *arg);

/* cleanup.c */
void				ph_cleanup(t_dinner *d, int stage);

#endif /* !PHILO_H */