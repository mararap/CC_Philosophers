/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:52:36 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/03 15:00:08 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* what philos do */

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
	if (p->dinner->philo_count == 1)
	{
		ph_print_status(p, "has taken a fork");
		return ;
	}
	pthread_mutex_lock(second);
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->last_meal_time = ph_get_time_ms();
	pthread_mutex_unlock(&p->dinner->meal_lock);
	ph_print_status(p, "has taken a fork");
	ph_print_status(p, "has taken a fork");
}

void	ph_eat(t_philo *p)
{
	long long	start;
	long long	end;

	if (p->dinner->philo_count == 1)
	{
		while (!ph_is_sim_over(p->dinner))
			usleep(500);
		return ;
	}
	start = p->last_meal_time;
	end = start + p->dinner->time_to_eat;
	ph_print_status(p, "is eating");
	while (ph_get_time_ms() < end && !ph_is_sim_over(p->dinner))
		usleep(75);
	pthread_mutex_lock(&p->dinner->meal_lock);
	p->meal_count++;
	pthread_mutex_unlock(&p->dinner->meal_lock);
}

void	ph_drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left);
	if (p->dinner->philo_count > 1)
		pthread_mutex_unlock(p->right);
}

void	ph_sleep(t_philo *p)
{
	long long	start;
	long long	end;

	start = ph_get_time_ms();
	end = start + p->dinner->time_to_sleep;
	ph_print_status(p, "is sleeping");
	while (ph_get_time_ms() < end && !ph_is_sim_over(p->dinner))
		usleep(75);
}

void	ph_think(t_philo *p)
{
	long long	think;
	long long	start;
	long long	end;

	start = ph_get_time_ms();
	ph_print_status(p, "is thinking");
	if (p->dinner->philo_count % 2 == 0)
		think = 1;
	else
		think = p->dinner->time_to_eat - p->dinner->time_to_sleep + 1;
	end = start + think;
	while (think > 0 && ph_get_time_ms() < end && !ph_is_sim_over(p->dinner))
		usleep(75);
}
