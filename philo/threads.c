/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:01:35 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/06 20:03:39 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Read simulation stop flag under mutex protection. */
int	ph_is_done(t_dinner *d)
{
	int	result;

	pthread_mutex_lock(&d->done_lock);
	result = d->is_done;
	pthread_mutex_unlock(&d->done_lock);
	return (result);
}

/*
Staggered start: even IDs wait one eat-time before first fork attempt.
This reduces startup contention and helps reach a stable lock pattern early.
*/
static void	*ph_routine(void *arg)
{
	t_philo		*p;
	long long	end;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->last_meal = p->dinner->start_time;
	pthread_mutex_unlock(&p->dinner->meal_lock);
	if (p->id % 2 == 0)
	{
		end = ph_get_time_us() + p->dinner->tte;
		while (ph_get_time_us() < end && !ph_is_done(p->dinner))
			usleep(100);
	}
	while (!ph_is_done(p->dinner))
	{
		ph_take_forks(p);
		ph_eat(p);
		ph_drop_forks(p);
		ph_sleep(p);
		ph_think(p);
	}
	return (NULL);
}

/* Join only the first n already-created threads (reverse order). */
static void	ph_join_threads(t_dinner *d, int n)
{
	while (n > 0)
	{
		n--;
		pthread_join(d->philos[n].tid, NULL);
	}
}

/* Start all philosopher threads; on failure stop and join created ones. */
int	ph_start_threads(t_dinner *d)
{
	int	i;

	i = 0;
	while (i < d->philo_count)
	{
		if (pthread_create(&d->philos[i].tid, NULL, ph_routine,
				&d->philos[i]) != 0)
		{
			pthread_mutex_lock(&d->done_lock);
			d->is_done = 1;
			pthread_mutex_unlock(&d->done_lock);
			ph_join_threads(d, i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < d->philo_count)
	{
		pthread_join(d->philos[i].tid, NULL);
		i++;
	}
	return (0);
}
