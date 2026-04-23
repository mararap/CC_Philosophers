/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:12 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/23 14:14:51 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Monitoring logic (death, meal count)
#include "philo.h"

static int	all_fed(t_dinner *d)
{
	int	i;
	int	fed;

	i = 0;
	fed = 0;
	if (d->meals_required == -1)
		return (0);
	pthread_mutex_lock(&d->meal_lock);
	while (i < d->philo_count)
	{
		if (d->philo_arr[i].meal_count >= d->meals_required)
			fed++;
		i++;
	}
	pthread_mutex_unlock(&d->meal_lock);
	if (fed == d->philo_count)
		return (1);
	return (0);
}

void	*ph_monitor(void *arg)
{
	int			i;
	t_dinner	*d;
	long long	timestamp;

	d = (t_dinner *)arg;
	i = 0;
	while (!ph_is_sim_over)
	{
		while (i < d->philo_count)
		{
			pthread_mutex_lock(&d->meal_lock);
			if ((ph_get_time_ms() - d->philo_arr[i].last_meal_time)
				> d->time_to_die)
			{
				pthread_mutex_lock(&d->print_lock);
				pthread_mutex_lock(&d->dead_lock);
				timestamp = ph_get_time_ms() - d->start_time;
				printf("%lld %d %s\n", timestamp, d->philo_arr[i].id, "died");
				d->is_dead = 1;
				pthread_mutex_unlock(&d->dead_lock);
				pthread_mutex_unlock(&d->print_lock);
			}
			ph_mutex_unlock(&d->meal_lock);
			if (all_fed(d))
			{
				pthread_mutex_lock(&d->dead_lock);
				d->is_dead = 1;
				pthread_mutex_unlock(&d->dead_lock);
			}
			i++;
			usleep(500);
		}
	}
	return (NULL);
}
