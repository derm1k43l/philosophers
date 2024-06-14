/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:35 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/13 10:48:47 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_sync(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->sim_mutex);
	while (!simulation->sync_ready)
	{
		pthread_mutex_unlock(&simulation->sim_mutex);
		ft_usleep(simulation, 1);
		pthread_mutex_lock(&simulation->sim_mutex);
	}
	pthread_mutex_unlock(&simulation->sim_mutex);
}

// Staging for avoiding deadlocks
// If the number of philosophers is even, 
// desynchronize the even ID philosophers by 2e4/20ms
// If the number of philosophers is odd, calculate the thinking time
// Desynchronize by sleeping for half of the calculated thinking time
void	desync(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	if (philo->simulation->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->simulation, 2e4);
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			t_eat = philo->simulation->time_to_eat;
			t_sleep = philo->simulation->time_to_sleep;
			t_think = (t_eat * 2) - t_sleep;
			if (t_think < 0)
				t_think = 0;
			ft_usleep(philo->simulation, t_think * 0.5);
		}
	}
}

bool	simulation_status(t_simulation *simulation)
{
	bool	status;

	pthread_mutex_lock(&simulation->sim_mutex);
	status = simulation->simulation_running;
	pthread_mutex_unlock(&simulation->sim_mutex);
	return (status);
}
bool	check_bool(t_mtx *mutex, bool *value)
{
	bool	status;

	pthread_mutex_lock(mutex);
	status = *value;
	pthread_mutex_unlock(mutex);
	return (status);
}
