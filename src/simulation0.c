/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/18 14:13:18 by mrusu            ###   ########.fr       */
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
	set_sync(simulation, true);
	i = -1;
	while (++i < simulation->philo_nbr)
	{
		pthread_join(simulation->philosophers[i].id_thread, NULL);
		printf("Philosopher %d joined\n", i + 1); // Debug print
	}
	pthread_join(simulation->monitor, NULL);
	printf("Monitor joined\n"); // Debug print
	set_sync(simulation, false);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, TAKE_RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKE_LEFT_FORK);
	set_last_meal_time(philo, ft_gettime(MILLISECOND));
	increment_meals_index(philo);
	print_status(philo, EATING);
	ft_usleep(philo->simulation, philo->simulation->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_sync(philo->simulation);
	set_last_meal_time(philo, ft_gettime(MILLISECOND));
	increase_threads_running(philo->simulation);
	if (philo->simulation->philo_nbr == 1)
		return (unus_philosophus(data));
	desync(philo);
	while (get_simulation_status(philo->simulation))
	{
		if (philo->full)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
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
	set_last_meal_time(philo, ft_gettime(MILLISECOND));
	print_status(philo, TAKE_RIGHT_FORK);
	while (get_simulation_status(philo->simulation))
	{
		ft_usleep(philo->simulation, philo->simulation->time_to_die);
		if (!get_simulation_status(philo->simulation))
			break ;
	}
	return (NULL);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;


	if (is_philo_full(philo))
		return (false);
	elapsed = ft_gettime(MILLISECOND) - philo->last_meal_time;
	t_to_die = philo->simulation->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	else
		return (false);
}
