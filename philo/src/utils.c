/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:37 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/28 15:42:48 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		printf(RED"Error with the memory \
			allocation, try again."RESET);
	return (ret);
}

void	clean(t_simulation *simulation)
{
	int	i;

	i = -1;
	if (simulation == NULL)
		return ;
	pthread_mutex_destroy(&simulation->print_mtx);
	pthread_mutex_destroy(&simulation->sim_mutex);
	if (simulation->forks)
	{
		while (++i < simulation->philo_nbr)
			pthread_mutex_destroy(&simulation->forks[i]);
		free(simulation->forks);
	}
	if (simulation->philosophers)
	{
		free(simulation->philosophers);
	}
}

long	ft_gettime(t_time code)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL))
	{
		printf("Could't get the system time.");
		return (-1);
	}
	if (code == MILLISECOND)
		return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	else if (code == MICROSECOND)
		return ((now.tv_sec * 1000000) + now.tv_usec);
	return (-1);
}

void	ft_usleep(t_simulation *simulation, long usecond)
{
	long	start;
	long	elapsed;
	long	rem;
	long	sleep;

	start = ft_gettime(MICROSECOND);
	rem = usecond;
	while (rem > 0 && get_status(&simulation->sim_mutex,
			&simulation->simulation_running))
	{
		elapsed = ft_gettime(MICROSECOND) - start;
		rem = usecond - elapsed;
		if (rem > 500)
			sleep = 500;
		else
			sleep = rem;
		if (sleep > 0)
		{
			usleep(sleep);
			rem -= sleep;
		}
	}
}

void	print_status(t_philo *philo, t_status status)
{
	long	timestamp;
	bool	status_sim;

	timestamp = ft_gettime(MILLISECOND) - philo->simulation->start_time;
	status_sim = get_status(&philo->simulation->sim_mutex,
			&philo->simulation->simulation_running);
	pthread_mutex_lock(&philo->simulation->print_mtx);
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->simulation->print_mtx);
		return ;
	}
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) && status_sim)
		printf("%-6ld %hd has taken a fork\n", timestamp, philo->id);
	else if (status == EATING && status_sim)
		printf("%-6ld %hd is eating\n", timestamp, philo->id);
	else if (status == SLEEPING && status_sim)
		printf("%-6ld %hd is sleeping\n", timestamp, philo->id);
	else if (status == THINKING && status_sim)
		printf("%-6ld %hd is thinking\n", timestamp, philo->id);
	else if (status == DIED && !status_sim)
		printf("%-6ld %hd died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->simulation->print_mtx);
}
