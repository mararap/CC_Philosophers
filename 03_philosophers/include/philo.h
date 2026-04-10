/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:14:34 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/10 10:06:07 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef pthread_mutex_t	t_fork_lock;
typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct s_philo
{
	int					id;
	pthread_t			tid; // thread-handle
	long long			last_meal_time;
	int					meal_count;
	t_fork_lock			*left;
	t_fork_lock			*right;
	t_dinner			*dinner;
};

struct s_dinner
{
	int					philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			start_time;
	int					meals_required;
	t_philo				*philo_arr;
	t_fork_lock			*forks_arr;
	int					is_dead;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
};

// UTILS

int						ph_atoui(const char *str);
long long				ph_get_time_ms(void);
void					ph_print_status(t_philo *philo, char *msg);


// Add your structs, function prototypes, and macros here

#endif //!PHILO_H
