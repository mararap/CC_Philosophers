/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:05:03 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/05 20:24:14 by marapovi         ###   ########.fr       */
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

/* 
calls gettimeofday and adds up the returned secons - converted
to microseconds - and the returned microseconds. this improves
accuracy, because performing the calculations with milliseconds
would cause rounding errors up to 1 microsecond per loop
(adding up).
 */
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

	end = ph_get_time_us() + us;
	while (ph_get_time_us() < end && !ph_is_done(d))
		usleep(100);
}

/* 
prints status message under print_lock and done_lock if p->dinner->is_done
still has value 0.
as times are dealt in microseconds until here, the value of timestamp
needs to be divided by 1000 to convert to milliseconds.
 */
void	ph_print(t_philo *p, const char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&p->dinner->print_lock);
	pthread_mutex_lock(&p->dinner->done_lock);
	if (!p->dinner->is_done)
	{
		timestamp = (ph_get_time_us() - p->dinner->start_time) / 1000;
		printf("%lld %d %s\n", timestamp, p->id, msg);
	}
	pthread_mutex_unlock(&p->dinner->done_lock);
	pthread_mutex_unlock(&p->dinner->print_lock);
}
