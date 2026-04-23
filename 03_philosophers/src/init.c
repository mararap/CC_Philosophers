/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/23 16:29:43 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Initialization (parsing, struct setup)
#include "philo.h"

int	ph_init_dinner(t_dinner *d)
{
	d->philo_arr = NULL;
	d->forks_arr = NULL;
	d->philo_arr = malloc(sizeof(t_philo) * d->philo_count);
	if (!d->philo_arr)
		return (1);
	d->forks_arr = malloc(sizeof(t_fork_lock) * d->philo_count);
	if (!d->forks_arr || (pthread_mutex_init(&d->print_lock, NULL) != 0))
	{
		ph_free_arrays(d);
		return (1);
	}
	if (pthread_mutex_init(&d->dead_lock, NULL) != 0)
	{
		ph_destroy_mutexes(d, 1);
		return (1);
	}
	if (pthread_mutex_init(&d->meal_lock, NULL) != 0)
	{
		ph_destroy_mutexes(d, 2);
		return (1);
	}
	d->is_dead = 0;
	return (0);
}

int	ph_init_forks(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		if (pthread_mutex_init(&d->forks_arr[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&d->forks_arr[i]);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ph_init_philos(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		d->philo_arr[i].id = i + 1;
		d->philo_arr[i].meal_count = 0;
		d->philo_arr[i].last_meal_time = d->start_time;
		d->philo_arr[i].left = &d->forks_arr[i];
		d->philo_arr[i].right = &d->forks_arr[(i + 1) % d->philo_count];
		d->philo_arr[i].dinner = d;
		i++;
	}
	return (0);
}
