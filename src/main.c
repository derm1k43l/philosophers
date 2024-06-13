/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:31 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/13 10:32:37 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_dinner(void *data)
{
	int				i;
	t_simulation	*simulation;

	simulation = (t_simulation *)data;
	while (simulation->threads_running_nbr < simulation->philo_nbr)
	{
		ft_usleep(simulation, 1);
	}
	while (simulation_status(simulation))
	{
		i = -1;
		while (++i < simulation->philo_nbr && simulation_status(simulation))
		{
			if (philo_died(simulation->philosophers + i))
			{
				pthread_mutex_lock(&simulation->sim_mutex);
				simulation->simulation_running = false;
				pthread_mutex_unlock(&simulation->sim_mutex);
				print_status(simulation->philosophers + i, DIED);
			}
		}
	}
	return (NULL);
}

