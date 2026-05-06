/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 13:41:38 by marapovi          #+#    #+#             */
/*   Updated: 2026/05/06 19:51:52 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
checks for invalid input and saves values into designated variables
 */
static int	ph_parse_args(int ac, char **av, t_dinner *d)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		write(2, "invalid input\nusage: ./philo N ttd tte tts [meals]\n", 52);
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (ph_atoull(av[i]) == -1)
			return (write(2, "invalid argument(s)\n", 21), 1);
		i++;
	}
	d->philo_count = (int)ph_atoull(av[1]);
	if (d->philo_count <= 0)
		return (write(2, "invalid input\n", 15), 1);
	d->ttd = ph_atoull(av[2]) * 1000;
	d->tte = ph_atoull(av[3]) * 1000;
	d->tts = ph_atoull(av[4]) * 1000;
	if (av[5])
		d->meals_required = (int)ph_atoull(av[5]);
	else
		d->meals_required = -1;
	return (0);
}

/* 
launches, coordinates and finally exits the program:
	1) parsing
	2) initialisation of structs and variables
	3) creates & joins threads
	4) cleans up
	5) returns 0 on success, 1 on error
 */
int	main(int ac, char **av)
{
	t_dinner	dinner;
	pthread_t	monitor_tid;

	if (ph_parse_args(ac, av, &dinner) != 0)
		return (1);
	if (ph_init_dinner(&dinner) != 0)
		return (1);
	if (ph_init_forks(&dinner) != 0)
		return (ph_cleanup(&dinner, 3), 1);
	dinner.start_time = ph_get_time_us();
	ph_init_philos(&dinner);
	if (pthread_create(&monitor_tid, NULL, ph_monitor, &dinner) != 0)
		return (ph_cleanup(&dinner, 3), 1);
	ph_start_threads(&dinner);
	pthread_join(monitor_tid, NULL);
	ph_cleanup(&dinner, 3);
	return (0);
}
