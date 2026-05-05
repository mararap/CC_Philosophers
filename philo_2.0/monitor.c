/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:52:29 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/05 10:47:40 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_fed(t_dinner *d)
{
	int	i;
	int	fed;

	if (d->meals_required == -1)
		return (0);
	fed = 0;
	pthread_mutex_lock(&d->meal_lock);
	i = 0;
	while (i < d->philo_count)
	{
		if (d->philos[i].meal_count >= d->meals_required)
			fed++;
		i++;
	}
	pthread_mutex_unlock(&d->meal_lock);
	if (fed == d->philo_count)
		return (1);
	return (0);
}

static void	report_death(t_dinner *d, int idx)
{
	long long	timestamp;

	pthread_mutex_lock(&d->print_lock);
	pthread_mutex_lock(&d->done_lock);
	if (!d->is_done)
	{
		timestamp = (ph_get_time_us() - d->start_time) / 1000;
		printf("%lld %d died\n", timestamp, d->philos[idx].id);
		d->is_done = 1;
	}
	pthread_mutex_unlock(&d->done_lock);
	pthread_mutex_unlock(&d->print_lock);
}

static void	stop_sim(t_dinner *d)
{
	pthread_mutex_lock(&d->done_lock);
	d->is_done = 1;
	pthread_mutex_unlock(&d->done_lock);
}

void	*ph_monitor(void *arg)
{
	t_dinner	*d;
	long long	last_meal;
	int			i;

	d = (t_dinner *)arg;
	while (!ph_is_done(d))
	{
		i = 0;
		while (i < d->philo_count)
		{
			pthread_mutex_lock(&d->meal_lock);
			last_meal = d->philos[i].last_meal;
			pthread_mutex_unlock(&d->meal_lock);
			if (ph_get_time_us() - last_meal > d->ttd)
				return (report_death(d, i), NULL);
			i++;
		}
		if (all_fed(d))
			return (stop_sim(d), NULL);
		usleep(500);
	}
	return (NULL);
}
