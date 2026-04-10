/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:17 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/10 12:30:40 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Philosopher thread routine and logic
#include "philo.h"

void	ph_take_forks(t_philo *p)
{
	t_fork_lock	*first;
	t_fork_lock	*second;
	
	first = p->left;
	second = p->right;
	if (first > second)
	{
		first = p->right;
		second = p->left;
	}
	pthread_mutex_lock(first);
	ph_print_status(p, "has taken a fork");
	pthread_mutex_lock(second);
	ph_print_status(p, "has taken a fork");
}

void	ph_drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
}

void	*ph_routine(void *arg)
{
	t_philo	*philo;
	while (!is_sim_over(philo->dinner))
	{
		ph_take_forks(philo);
		ph_eat(philo);
		ph_drop_forks(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

