/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:04 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/29 12:08:17 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	data_init(t_simulation *simulation)
{
	int	i;

	i = -1;
	if (simulation == NULL || simulation->philo_nbr <= 0)
		return (error_clean(simulation, "Memory allocation failed"));
	simulation->simulation_running = true;
	simulation->sync_ready = false;
	simulation->threads_running_nbr = 0;
	simulation->philosophers = ft_malloc(sizeof(t_philo) \
		* simulation->philo_nbr);
	simulation->forks = ft_malloc(sizeof(t_mtx) * simulation->philo_nbr);
	if (simulation->philosophers == NULL || simulation->forks == NULL)
		return (error_clean(simulation, "Memory allocation failed"));
	if (pthread_mutex_init(&simulation->print_mtx, NULL) != 0
		|| pthread_mutex_init(&simulation->sim_mutex, NULL) != 0)
		return (error_clean(simulation, "Mutex init failed"));
	while (++i < simulation->philo_nbr)
	{
		if ((pthread_mutex_init(&simulation->forks[i], NULL) != 0))
			return (error_clean(simulation, "Mutex init failed"));
	}
	return (philo_init(simulation));
}

int	philo_init(t_simulation *simulation)
{
	t_philo	*philo;	
	int		i;

	i = -1;
	if (simulation == NULL || simulation->philo_nbr <= 0
		|| simulation->philosophers == NULL)
	{
		return (error_clean(simulation, "Invali structure or data."));
	}
	ft_usleep(simulation, 10);
	while (++i < simulation->philo_nbr)
	{
		philo = &simulation->philosophers[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meals_index = 0;
		philo->simulation = simulation;
		assign_forks(philo, simulation->forks);
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
		{
			return (error_clean(simulation, "Failed to init mutex philo"));
		}
	}
	return (0);
}

void	assign_forks(t_philo *philo, t_mtx *forks)
{
	int	philo_id;
	int	philo_nbr;

	if (philo == NULL || forks == NULL || philo->simulation == NULL)
	{
		printf("Invalid philosopher or fork data.");
		return ;
	}
	philo_id = philo->id - 1;
	philo_nbr = philo->simulation->philo_nbr;
	philo->right_fork = &forks[philo_id];
	philo->left_fork = &forks[(philo_id + 1) % philo_nbr];
}

void	forks_lock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, TAKE_RIGHT_FORK);
	print_status(philo, TAKE_LEFT_FORK);
}
