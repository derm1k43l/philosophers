/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:00:34 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/18 14:38:26 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_simulation(t_simulation *simulation, bool status)
{
	pthread_mutex_lock(&simulation->sim_mutex);
	simulation->simulation_running = status;
	pthread_mutex_unlock(&simulation->sim_mutex);
}

void	set_sync(t_simulation *simulation, bool status)
{
	pthread_mutex_lock(&simulation->sim_mutex);
	simulation->sync_ready = status;
	pthread_mutex_unlock(&simulation->sim_mutex);
}

void	set_last_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->philo_mutex);
}

long	get_last_meal_time(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_mutex);
	time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mutex);

	return (time);
}

void	increment_meals_index(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_index++;
	if (philo->meals_index == philo->simulation->limit_meals)
		philo->full = true;
	pthread_mutex_unlock(&philo->philo_mutex);
}

bool	is_philo_full(t_philo *philo)
{
	bool	full;

	pthread_mutex_lock(&philo->philo_mutex);
	full = philo->full;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (full);
}
