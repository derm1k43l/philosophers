/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:00:34 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/20 17:46:53 by mrusu            ###   ########.fr       */
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
