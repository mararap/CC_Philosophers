/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:12 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/03 21:24:36 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Monitoring logic (death, meal count) */

#include "philo.h"

static int	all_fed(t_dinner *d)
{
	int	i;
	int	fed;

	i = 0;
	fed = 0;
	if (d->meals_required == -1)
		return (0);
	while (i < d->philo_count)
	{
		pthread_mutex_lock(&d->meal_lock);
		if (d->philo_arr[i].meal_count >= d->meals_required)
			fed++;
		pthread_mutex_unlock(&d->meal_lock);
		i++;
	}
	if (fed == d->philo_count)
		return (1);
	return (0);
}

static void	report_death(t_dinner *d, int id)
{
	long long	timestamp;

	timestamp = ph_get_time_ms() - d->start_time;
	pthread_mutex_lock(&d->print_lock);
	pthread_mutex_lock(&d->dead_lock);
	if (!d->is_dead)
	{
		printf("%lld %d %s\n", timestamp, d->philo_arr[id].id, "died");
		d->is_dead = 1;
	}
	pthread_mutex_unlock(&d->dead_lock);
	pthread_mutex_unlock(&d->print_lock);
}

static void	stop_sim(t_dinner *d)
{
	pthread_mutex_lock(&d->print_lock);
	pthread_mutex_lock(&d->dead_lock);
	d->is_dead = 1;
	pthread_mutex_unlock(&d->dead_lock);
	pthread_mutex_unlock(&d->print_lock);
}

void	*ph_monitor(void *arg)
{
	int			i;
	t_dinner	*d;
	long long	last_meal;

	d = (t_dinner *)arg;
	while (!ph_is_sim_over(d))
	{
		i = 0;
		while (i < d->philo_count)
		{
			pthread_mutex_lock(&d->meal_lock);
			last_meal = d->philo_arr[i].last_meal_time;
			pthread_mutex_unlock(&d->meal_lock);
			if ((ph_get_time_ms() - last_meal) > d->time_to_die
				&& !ph_is_sim_over(d))
				report_death(d, i);
			i++;
		}
		if (all_fed(d))
			stop_sim(d);
		usleep(75);
	}
	return (NULL);
}
