/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/10 12:30:48 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Initialization (parsing, struct setup)
#include "philo.h"

void	init_dinner(t_dinner d)
{
	
}

void	init_forks(t_fork_lock f)
{
	
}
void	init_philos(t_philo p)
{
	
}

int	start_threads(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		if (pthread_create(&d->philo_arr[i].tid, NULL, ph_routine,
				&d->philo_arr[i] != 0))
			return (1);
		i++;
	}
	i = 0;
	while (i < d->philo_count)
	{
		pthread_join(d->philo_arr[i].tid, NULL);
		i++;
	}
	return (0);
}