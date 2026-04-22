/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:10:50 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/22 19:12:23 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Resource cleanup/freeing
#include "philo.h"

void	ph_free_arrays(t_dinner *d)
{
	if (d->forks_arr)
	{
		free(d->forks_arr);
		d->forks_arr = NULL;
	}
	if (d->philo_arr)
	{
		free(d->philo_arr);
		d->philo_arr = NULL;
	}
}

void	ph_destroy_mutexes(t_dinner *d, int stage)
{
	if (stage >= 3)
		pthread_mutex_destroy(&d->meal_lock);
	if (stage >= 2)
		pthread_mutex_destroy(&d->dead_lock);
	if (stage >= 1)
		pthread_mutex_destroy(&d->print_lock);
	ph_free_arrays(d);
}
