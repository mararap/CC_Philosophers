/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:11:07 by marapovi          #+#    #+#             */
/*   Updated: 2026/04/22 19:13:14 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Entry point
#include "philo.h"

static int ph_parse_av(int ac, char **av, t_dinner *d)
{
    int i;

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

int main(int ac, char **av)
{
    t_dinner dinner;
    
    if (ph_parse_av(ac, av, &dinner) != 0)
        return (1);
    ph_init_dinner(&dinner);
    ph_init_forks(&dinner);
    dinner.start_time = ph_get_time_ms();
    ph_init_philos(&dinner);
    ph_start_threads(&dinner);
    
    // initalize data
    // create philo threads
    // run routine for each philo
    // run/start monitor
    // wait for threads with pthread_join
    // cleanup
    return 0;
}
