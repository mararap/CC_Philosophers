/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:14:34 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/08 13:14:23 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// typedef pthread_mutex_t t_fork;	// dominic tipp

typedef struct s_fork t_fork;
typedef struct s_philo t_philo;
typedef struct s_dinner t_dinner;

struct s_fork
{
	pthread_mutex_t	lock;
};

struct s_philo
{
	size_t		id;
	pthread_t	tid; // thread-handle
	long long	last_meal_time;
	size_t		meal_count;
	t_fork		*left;
	t_fork		*right;
	t_dinner	*dinner;
};

struct s_dinner
{
	size_t			number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	size_t			number_of_times_each_philosopher_must_eat;
	size_t			meals_required;
	t_philo			*philo_arr;
	t_fork			*forks_arr;
	int				dead;
	pthread_mutex_t	print;
};


// Add your structs, function prototypes, and macros here

#endif //!PHILO_H
