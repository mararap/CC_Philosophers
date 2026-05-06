/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 09:01:35 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/06 00:50:01 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_is_done(t_dinner *d)
{
	int	result;

	pthread_mutex_lock(&d->done_lock);
	result = d->is_done;
	pthread_mutex_unlock(&d->done_lock);
	return (result);
}

/* 
Staggert start: even-ID philosophers wait one tte before their first
fork grab. This lets all odd-ID philosophers acquire their first fork
uncontested, so the table reaches a stable alterning pattern from
the very first round rather than having all philosophers compete for
forks at the same time on startup.
 */
static void	*ph_routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->last_meal = p->dinner->start_time;
	pthread_mutex_unlock(&p->dinner->meal_lock);
	if (p->id % 2)
		ph_wait_us(p->dinner->tte / 2, p->dinner);
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

static void	ph_join_threads(t_dinner *d, int n)
{
	while (n > 0)
	{
		n--;
		pthread_join(d->philos[n].tid, NULL);
	}
}

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
