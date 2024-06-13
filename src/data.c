/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:04 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/13 10:19:02 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	data_init(t_simulation *simulation)
{
	int	i;

	i = -1;
	simulation->simulation_running = true;
	simulation->sync_ready = false;
	simulation->threads_running_nbr = 0;
	simulation->philosophers = ft_malloc(sizeof(t_philo) \
		* simulation->philo_nbr);
	simulation->forks = ft_malloc(sizeof(t_mtx) * simulation->philo_nbr);
	pthread_mutex_init(&simulation->print_mtx, NULL);
	pthread_mutex_init(&simulation->sim_mutex, NULL);
	while (++i < simulation->philo_nbr)
	{
		pthread_mutex_init(&simulation->forks[i], NULL);
	}
	philo_init(simulation);
}

void	philo_init(t_simulation *simulation)
{
	t_philo	*philo;	
	int		i;

	i = -1;
	while (++i < simulation->philo_nbr)
	{
		philo = &simulation->philosophers[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meals_index = 0;
		philo->simulation = simulation;
		assign_forks(philo, simulation->forks);
	}
}

void	assign_forks(t_philo *philo, t_mtx *forks)
{
	int	philo_id;
	int	philo_nbr;

	philo_id = philo->id - 1;
	philo_nbr = philo->simulation->philo_nbr;
	philo->right_fork = &forks[philo_id];
	philo->left_fork = &forks[(philo_id + 1) % philo_nbr];
}
