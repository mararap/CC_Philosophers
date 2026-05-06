/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:05:03 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/06 15:50:49 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ph_atoull(const char *str)
{
	long long	result;
	int			i;

	if (!str || !str[0])
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

long long	ph_get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000000 + tv.tv_usec));
}

/* Sleep for 'us' microseconds, waking early if simulation ends. */
void	ph_wait_us(long long us, t_dinner *d)
{
	long long	end;
	long long	now;
	
	end = ph_get_time_us() + us;
	while (!ph_is_done(d))
	{
		now = ph_get_time_us();
		if (now >= end)
			break ;
		if (end - now > 2000)
			usleep(500);
		if (end - now > 500)
			usleep(100);
		else
			usleep(20);
	}
}

void	ph_print(t_philo *p, const char *msg)
{
	long long	ts;

	pthread_mutex_lock(&p->dinner->print_lock);
	pthread_mutex_lock(&p->dinner->done_lock);
	if (!p->dinner->is_done)
	{
		ts = (ph_get_time_us() - p->dinner->start_time) / 1000;
		printf("%lld %d %s\n", ts, p->id, msg);
	}
	pthread_mutex_unlock(&p->dinner->done_lock);
	pthread_mutex_unlock(&p->dinner->print_lock);
}
