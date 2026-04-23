/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:52:36 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/23 12:37:25 by marapovi         ###   ########.fr       */
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
	long long start;
	
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->last_meal_time = ph_get_time_ms();
	start = p->last_meal_time;
	p->meal_count++;
	pthread_mutex_unlock(&p->dinner->meal_lock);
	ph_print_status(p, "is eating");	
	while (ph_get_time_ms() < start + p->dinner->time_to_eat &&
		!ph_is_sim_over(p->dinner))
	{
		usleep(500);
	}
}

void	ph_drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	pthread_mutex_unlock(p->right);
}

void	ph_sleep(t_philo *p)
{
	long long start;

	start = ph_get_time_ms();
	ph_print_status(p, "is sleeping");
	while (ph_get_time_ms() < start + p->dinner->time_to_sleep &&
		!ph_is_sim_over(p->dinner))
	{
		usleep(500);
	}
}

void	ph_think(t_philo *p)
{
	ph_print_status(p, "is thinking");
}
