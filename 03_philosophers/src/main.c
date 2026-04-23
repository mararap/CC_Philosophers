/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:07 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/23 16:36:47 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Entry point
#include "philo.h"

// check number of arguments
// check validity of arguments
// parse arguments
static int	ph_parse_av(int ac, char **av, t_dinner *d)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (write(2, "wrong number of arguments\n", 26), 1);
	i = 1;
	while (i < ac)
	{
		if (ph_atoui(av[i]) == -1)
			return (write(2, "invalid argument(s)\n", 20), 1);
		i++;
	}
	d->philo_count = ph_atoui(av[1]);
	if (d->philo_count <= 0)
		return (write(2, "invalid argument(s)\n", 20), 1);
	d->time_to_die = ph_atoui(av[2]);
	d->time_to_eat = ph_atoui(av[3]);
	d->time_to_sleep = ph_atoui(av[4]);
	if (ac == 6)
		d->meals_required = ph_atoui(av[5]);
	else
		d->meals_required = -1;
	return (0);
}

// initalize data
// run/start monitor
// create philo threads
// run routine for each philo
// wait for threads with pthread_join
// cleanup
int	main(int ac, char **av)
{
	t_dinner	dinner;
	pthread_t	monitor_tid;

	if (ph_parse_av(ac, av, &dinner) != 0)
		return (1);
	if (ph_init_dinner(&dinner) != 0)
		return (1);
	if (ph_init_forks(&dinner) != 0)
		return (ph_destroy_mutexes(&dinner, 3), 1);
	dinner.start_time = ph_get_time_ms();
	ph_init_philos(&dinner);
	if (pthread_create(&monitor_tid, NULL, ph_monitor, &dinner) != 0)
		return (ph_destroy_mutexes(&dinner, 3), 1);
	if (ph_start_philo_threads(&dinner) != 0)
	{
		pthread_join(monitor_tid, NULL);
		ph_destroy_mutexes(&dinner, 3);
		return (1);
	}
	pthread_join(monitor_tid, NULL);
	ph_destroy_mutexes(&dinner, 3);
	return (0);
}
