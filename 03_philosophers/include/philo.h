/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:14:34 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/07 15:05:39 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
	size_t		id;
	pthread_t	tid;
	// thread-handle
	long long	last_meal_time;
	size_t		meal_count;
}			t_philo;




// Add your structs, function prototypes, and macros here

#endif //!PHILO_H
