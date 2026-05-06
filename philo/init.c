/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:07:51 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/06 19:52:33 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
initializes dinner struct:
	sets variables/pointers to 0/NULL
	allocates memory & checks for malloc failure
	initializes threads & checks for failure
	calls cleanup if needed
	returns 0 on success, 1 on error
 */
int	ph_init_dinner(t_dinner *d)
{
	d->philos = NULL;
	d->forks = NULL;
	d->forks_init = 0;
	d->is_done = 0;
	d->philos = malloc(sizeof(t_philo) * d->philo_count);
	if (!d->philos)
		return (1);
	d->forks = malloc(sizeof(t_fork) * d->philo_count);
	if (!d->forks)
		return (free(d->philos), d->philos = NULL, 1);
	if (pthread_mutex_init(&d->print_lock, NULL) != 0)
		return (free(d->forks), free(d->philos), 1);
	if (pthread_mutex_init(&d->done_lock, NULL) != 0)
		return (ph_cleanup(d, 1), 1);
	if (pthread_mutex_init(&d->meal_lock, NULL) != 0)
		return (ph_cleanup(d, 2), 1);
	return (0);
}

/* 
initializes forks array of mutexes:
	loops until number of forks is equal to number of philos,
	initializing one mutex in each loop and adding it to forks-array.
	on failure, destroys as many fork mutexes as have been created by
	looping over the array backwards.
	returns 0 on success, 1 on error.
 */
int	ph_init_forks(t_dinner *d)
{
	while (d->forks_init < d->philo_count)
	{
		if (pthread_mutex_init(&d->forks[d->forks_init], NULL) != 0)
		{
			while (d->forks_init > 0)
			{
				d->forks_init--;
				pthread_mutex_destroy(&d->forks[d->forks_init]);
			}
			return (1);
		}
		d->forks_init++;
	}
	return (0);
}

/* 
initializes philo array of structs:
	loops until number of philos is reached, filling each struct
	with data. uses `% d->philo_count` to assign fork idx 0 to
	first AND LAST philo.
 */
void	ph_init_philos(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		d->philos[i].id = i + 1;
		d->philos[i].meal_count = 0;
		d->philos[i].last_meal = d->start_time;
		d->philos[i].left = &d->forks[i];
		d->philos[i].right = &d->forks[(i + 1) % d->philo_count];
		d->philos[i].dinner = d;
		i++;
	}
}
