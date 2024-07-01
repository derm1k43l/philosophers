/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:35 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/28 15:44:44 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_sync(t_simulation *simulation)
{
	while (!get_status(&simulation->sim_mutex, &simulation->sync_ready))
	{
		ft_usleep(simulation, 1);
	}
}

bool	all_threads_active(t_mtx *mtx, short *threads, short philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mtx);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mtx);
	return (ret);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_status(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ft_gettime(MILLISECOND) - get_last_meal_time(philo);
	if (elapsed > philo->simulation->time_to_die / 1000)
		return (true);
	else
		return (false);
}

bool	all_philos_full(t_simulation *simulation)
{
	int	i;
	int	full_c;

	i = -1;
	full_c = 0;
	while (++i < simulation->philo_nbr)
	{
		if (get_status(&simulation->philosophers[i].philo_mutex,
				&simulation->philosophers[i].full))
			full_c++;
	}
	if (full_c == simulation->philo_nbr)
	{
		set_status(&simulation->sim_mutex,
			&simulation->simulation_running, false);
		return (true);
	}
	return (false);
}
