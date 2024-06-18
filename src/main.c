/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:31 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/18 17:30:15 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_dinner(void *data)
{
	int				i;
	t_simulation	*simulation;

	simulation = (t_simulation *)data;
	while (!all_threads_active(&simulation->sim_mutex, \
		&simulation->threads_running_nbr, simulation->philo_nbr))
		ft_usleep(simulation, 1);
	while (get_simulation_status(simulation))
	{
		i = -1;
		while (++i < simulation->philo_nbr)
		{
			if (philo_died(simulation->philosophers + i))
			{
				set_simulation(simulation, false);
				print_status(simulation->philosophers + i, DIED);
			}
		}
		ft_usleep(simulation, 20);
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_simulation	simulation;

	if (ac == 5 || ac == 6)
	{
		input_check(&simulation, av);
		data_init(&simulation);
		start_simulation(&simulation);
		clean(&simulation);
	}
	else
	{
		error_exit("Usage ./philo 5 800 200 200");
	}
	return (0);
}
