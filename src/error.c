/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:20:27 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/14 10:53:36 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error)
{
	printf(R "%s \n" DEF, error);
	exit(EXIT_FAILURE);
}

//need to unlock before return!! 

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->philo_mutex); 
		return (false);
	}
	elapsed = ft_gettime(MILLISECOND) - philo->last_meal_time;
	pthread_mutex_unlock(&philo->philo_mutex);
	t_to_die = philo->simulation->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	else
		return (false);
}
