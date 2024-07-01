/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:31 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/28 14:13:35 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *data)
{
	int				i;
	t_simulation	*simulation;

	simulation = (t_simulation *)data;
	while (!all_threads_active(&simulation->sim_mutex, \
		&simulation->threads_running_nbr, simulation->philo_nbr))
		ft_usleep(simulation, 42);
	while (get_status(&simulation->sim_mutex, &simulation->simulation_running))
	{
		i = -1;
		while (++i < simulation->philo_nbr)
		{
			if (philo_died(simulation->philosophers + i))
			{
				set_status(&simulation->sim_mutex,
					&simulation->simulation_running, false);
				print_status(simulation->philosophers + i, DIED);
				return (NULL);
			}
			ft_usleep(simulation, 420);
		}
		if (all_philos_full(simulation))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_simulation	simulation;

	if (ac != 5 && ac != 6)
	{
		printf(RED"Usage: ./philo 5 800 200 200 [meals]\n" RESET);
		return (1);
	}
	if (input_check(&simulation, av) != 0 || data_init(&simulation) != 0)
		return (1);
	if (start_simulation(&simulation) != 0)
		return (error_clean(&simulation, "Simulation start failed."));
	clean(&simulation);
	return (0);
}
