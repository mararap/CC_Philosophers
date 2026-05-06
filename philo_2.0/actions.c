/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:22:39 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/05 11:49:22 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Parity-based deadlock prevention:
	Even ID -> left fork first, then right
	Odd ID -> right fork first, then left
At every adjacent pair, one philosopher goes left-first and the
other one goes right-first, so no circular wait can form.
Prints status with every locked fork. Sets p->last_meal to current
time at the very end.
 */
void	ph_take_forks(t_philo *p)
{
	t_fork	*first;
	t_fork	*second;

	if (p->dinner->philo_count == 1)
	{
		pthread_mutex_lock(p->left);
		ph_print(p, "has taken a fork");
		return ;
	}
	first = p->left;
	second = p->right;
	if (p->id % 2 == 0)
	{
		first = p->right;
		second = p->left;
	}
	pthread_mutex_lock(first);
	ph_print(p, "has taken a fork");
	pthread_mutex_lock(second);
	ph_print(p, "has taken a fork");
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->last_meal = ph_get_time_us();
	pthread_mutex_unlock(&p->dinner->meal_lock);
}

/* 
if there's only one philo, it just waits until dinner is done
aka the philo died of starvation.
otherwise, prints is eating and "eats" for `tte`.
increases p->meal_count by one under mutex lock.
 */
void	ph_eat(t_philo *p)
{
	if (p->dinner->philo_count == 1)
	{
		while (!ph_is_done(p->dinner))
			usleep(500);
		return ;
	}
	ph_print(p, "is eating");
	ph_wait_us(p->dinner->tte, p->dinner);
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->meal_count++;
	pthread_mutex_unlock(&p->dinner->meal_lock);
}

/* 
unlocks forks mutexes (only one if philo_count = 1)
 */
void	ph_drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	if (p->dinner->philo_count > 1)
		pthread_mutex_unlock(p->right);
}

/* 
prints "is sleeping" and "sleeps" for p->dinner->tts
 */
void	ph_sleep(t_philo *p)
{
	ph_print(p, "is sleeping");
	ph_wait_us(p->dinner->tts, p->dinner);
}

/*
Odd number of philos: one is always "left out" of each eating
round. They must wait long enough for a neighbour to complete a full
eat+sleep cycle before competing for the same fork again.

Minimum	wait = (2 * tte) - tts (derived from cycle alignment);
For even N, parity locking pairs everyone perfectly; no wait needed.
 */
void	ph_think(t_philo *p)
{
	long long	think_us;

	ph_print(p, "is thinking");
	if (p->dinner->philo_count % 2 == 0)
		return ;
	think_us = 2 * p->dinner->tte - p->dinner->tts;
	if (think_us <= 0)
		think_us = p->dinner->tte / 2;
	ph_wait_us(think_us, p->dinner);
}
