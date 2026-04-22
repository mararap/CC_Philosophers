/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:52:36 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/22 21:05:33 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ph_eat(t_philo *p)
{
	
}

void	ph_drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
}

void	ph_sleep(t_philo *p)
{
	
}

void	ph_think(t_philo *p)
{
	
}
