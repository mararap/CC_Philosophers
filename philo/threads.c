/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:17 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/27 00:20:33 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Philosopher thread routine and logic */

#include "philo.h"

int	ph_is_sim_over(t_dinner *d)
{
	pthread_mutex_lock(&d->dead_lock);
	if (d->is_dead)
	{
		pthread_mutex_unlock(&d->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&d->dead_lock);
	return (0);
}

static void	*ph_routine(void *arg)
{
	t_philo		*philo;
	long long	start;

	philo = (t_philo *)arg;
	start = ph_get_time_ms();
	pthread_mutex_lock(&philo->dinner->meal_lock);
	philo->last_meal_time = start;
	pthread_mutex_unlock(&philo->dinner->meal_lock);
	if (philo->id % 2 == 0)
	{
		while (ph_get_time_ms() < start + philo->dinner->time_to_eat
			&& !ph_is_sim_over(philo->dinner))
			usleep(75);
	}
	while (!ph_is_sim_over(philo->dinner))
	{
		ph_take_forks(philo);
		ph_eat(philo);
		ph_drop_forks(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

static void	ph_join_threads(t_dinner *d, int n)
{
	while (n >= 0)
	{
		pthread_join(d->philo_arr[n].tid, NULL);
		n--;
	}
}

int	ph_start_philo_threads(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		if (pthread_create(&d->philo_arr[i].tid, NULL, ph_routine,
				&d->philo_arr[i]) != 0)
		{
			pthread_mutex_lock(&d->dead_lock);
			d->is_dead = 1;
			pthread_mutex_unlock(&d->dead_lock);
			ph_join_threads(d, i - 1);
			return (1);
		}
		i++;
	}
	ph_join_threads(d, d->philo_count - 1);
	return (0);
}
