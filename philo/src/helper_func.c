/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:00:34 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/28 12:53:30 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_status(t_mtx *mutex, bool *dst, bool status)
{
	pthread_mutex_lock(mutex);
	*dst = status;
	pthread_mutex_unlock(mutex);
}

bool	get_status(t_mtx *mutex, bool *status)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *status;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_last_meal_time(t_philo *philo)
{
	long	time;

	time = ft_gettime(MILLISECOND);
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

void	increase_threads_running(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->sim_mutex);
	simulation->threads_running_nbr++;
	pthread_mutex_unlock(&simulation->sim_mutex);
}
