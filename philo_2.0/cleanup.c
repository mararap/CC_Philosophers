/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:26:29 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/05 10:31:49 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
stage: how many of the three shared mutexes were initalized:
	1 -> print lock only
	2 -> print lock = done_lock
	3 -> all three
 */
void	ph_cleanup(t_dinner *d, int stage)
{
	int	i;

	if (stage >= 3)
		pthread_mutex_destroy(&d->meal_lock);
	if (stage >= 2)
		pthread_mutex_destroy(&d->done_lock);
	if (stage >= 1)
		pthread_mutex_destroy(&d->print_lock);
	i = 0;
	while (i < d->forks_init)
	{
		pthread_mutex_destroy(&d->forks[i]);
		i++;
	}
	free(d->forks);
	free(d->philos);
	d->forks = NULL;
	d->philos = NULL;
}
