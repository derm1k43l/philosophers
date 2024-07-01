/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/29 13:14:21 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_simulation(t_simulation *simulation)
{
	int		*index;
	int		i;

	index = ft_malloc(simulation->philo_nbr * sizeof(int));
	if (simulation->limit_meals == 0)
	{
		free(index);
		return (1);
	}
	simulation->start_time = ft_gettime(MILLISECOND);
	set_status(&simulation->sim_mutex, &simulation->sync_ready, true);
	create_threads(simulation, index);
	if (pthread_create(&simulation->monitor, NULL, monitor, simulation) != 0)
		return (1);
	i = -1;
	while (++i < simulation->philo_nbr)
	{
		if (pthread_join(simulation->philosophers[i].id_thread, NULL) != 0)
			return (1);
	}
	set_status(&simulation->sim_mutex, &simulation->simulation_running, false);
	if (pthread_join(simulation->monitor, NULL) != 0)
		return (1);
	free(index);
	return (0);
}

int	create_threads(t_simulation *simulation, int *index)
{
	int		i;

	i = -1;
	while (++i < simulation->philo_nbr)
	{
		index[i] = i;
		simulation->philosophers[i].id = i + 1;
		if (simulation->philo_nbr == 1)
		{
			if (pthread_create(&simulation->philosophers[0].id_thread,
					NULL, unus_philosophus, &simulation->philosophers[0]) != 0)
				return (1);
			break ;
		}
		else
		{
			if (pthread_create(&simulation->philosophers[i].id_thread,
					NULL, dinner_routine,
					&simulation->philosophers[index[i]]) != 0)
				return (1);
		}
	}
	return (0);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_sync(philo->simulation);
	set_last_meal_time(philo);
	increase_threads_running(philo->simulation);
	print_status(philo, THINKING);
	while (get_status(&philo->simulation->sim_mutex,
			&philo->simulation->simulation_running))
	{
		if (get_status(&philo->philo_mutex, &philo->full))
			return (NULL);
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo->simulation, philo->simulation->time_to_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (!get_status(&philo->simulation->sim_mutex,
			&philo->simulation->simulation_running))
		return ;
	forks_lock(philo);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_index++;
	if (philo->meals_index == philo->simulation->limit_meals)
		philo->full = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	set_last_meal_time(philo);
	ft_usleep(philo->simulation, philo->simulation->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*unus_philosophus(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_last_meal_time(philo);
	print_status(philo, TAKE_RIGHT_FORK);
	increase_threads_running(philo->simulation);
	pthread_mutex_lock(&philo->simulation->sim_mutex);
	philo->simulation->sync_ready = true;
	pthread_mutex_unlock(&philo->simulation->sim_mutex);
	while (get_status(&philo->simulation->sim_mutex,
			&philo->simulation->simulation_running))
	{
		ft_usleep(philo->simulation, philo->simulation->time_to_die);
	}
	return (NULL);
}
