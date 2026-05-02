/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:22 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/02 23:27:28 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* globally used helpers */

#include "philo.h"

static char	is_usign_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ph_atoui(const char *str)
{
	int			i;
	long int	result;

	i = 0;
	result = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (str[i])
	{
		if (!is_usign_digit(str[i]))
			return (-1);
		result = result * 10 + str[i] - '0';
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

long long	ph_get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ph_print_status(t_philo *philo, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->dinner->print_lock);
	if (philo->dinner->is_dead)
	{
		pthread_mutex_unlock(&philo->dinner->print_lock);
		return ;
	}
	timestamp = ph_get_time_ms() - philo->dinner->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->dinner->print_lock);
}
