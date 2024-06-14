/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/14 13:39:18 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start_simulation(t_simulation *simulation)
{
	int	i;

	i = -1;
	if (simulation->limit_meals == 0)
		return ;
	while (++i < simulation->philo_nbr)
	{
		pthread_create(&simulation->philosophers[i].id_thread, \
				NULL, dinner_routine, &simulation->philosophers[i]);
	}
	pthread_create(&simulation->monitor, NULL, monitoring_dinner, simulation);
	simulation->start_time = ft_gettime(MILLISECOND);
	pthread_mutex_lock(&simulation->sim_mutex);
	simulation->sync_ready = true;
	pthread_mutex_unlock(&simulation->sim_mutex);
	i = -1;
	while (++i < simulation->philo_nbr)
	{
		pthread_join(simulation->philosophers[i].id_thread, NULL);
	}
	pthread_mutex_lock(&simulation->sim_mutex);
	simulation->simulation_running = false;
	pthread_mutex_unlock(&simulation->sim_mutex);
	pthread_join(simulation->monitor, NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, TAKE_RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKE_LEFT_FORK);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = ft_gettime(MILLISECOND);
	philo->meals_index++;
	if (philo->meals_index == philo->simulation->limit_meals)
	{
		philo->full = true;
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	print_status(philo, EATING);
	ft_usleep(philo->simulation, philo->simulation->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_sync(philo->simulation);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = ft_gettime(MILLISECOND);
	philo->simulation->threads_running_nbr++;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (philo->simulation->philo_nbr == 1)
		return (unus_philosophus(data));
	desync(philo);
	while (simulation_status(philo->simulation))
	{
		if (philo->full)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo->simulation, philo->simulation->time_to_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}

void	*unus_philosophus(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_sync(philo->simulation);
	philo->last_meal_time = ft_gettime(MILLISECOND);
	philo->simulation->threads_running_nbr++;
	print_status(philo, TAKE_RIGHT_FORK);
	while (simulation_status(philo->simulation))
	{
		ft_usleep(philo->simulation, philo->simulation->time_to_die);
		if (!simulation_status(philo->simulation))
			break ;
	}
	return (NULL);
}
