/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:37 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/13 10:37:04 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit(R"Error with the memory allocation, try again."DEF);
	return (ret);
}

void	clean(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->print_mtx);
	pthread_mutex_destroy(&simulation->sim_mutex);
	free(simulation->forks);
	free(simulation->philosophers);
}

long	ft_gettime(t_time code)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL))
		error_exit("Could't get the system time.");
	if (code == SECOND)
		return (now.tv_sec);
	else if (code == MILLISECOND)
		return ((now.tv_sec * 1e3) + (now.tv_usec / 1e3));
	else if (code == MICROSECOND)
		return ((now.tv_sec * 1e6) + now.tv_usec);
	else
		error_exit(R"Invalid time code."DEF);
	return (1);
}

void	ft_usleep(t_simulation *simulation, long usecond)
{
	long	start;
	long	elapsed;
	long	rem;
	long	sleep;

	start = ft_gettime(MICROSECOND);
	rem = usecond;
	while (rem > 0 && simulation_status(simulation))
	{
		elapsed = ft_gettime(MICROSECOND) - start;
		rem = usecond - elapsed;
		if (rem > 1000)
			sleep = 1000;
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
	long	elapsed;
	bool	status_sim;

	elapsed = ft_gettime(MILLISECOND) - philo->simulation->start_time;
	status_sim = simulation_status(philo->simulation);
	pthread_mutex_lock(&philo->simulation->print_mtx);
	if (philo->full)
		return ;
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) && status_sim)
		printf(W"%-6ld"DEF" %ld has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && status_sim)
		printf(W"%-6ld"B" %ld is eating\n"DEF, elapsed, philo->id);
	else if (status == SLEEPING && status_sim)
		printf(W"%-6ld"DEF" %ld is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && status_sim)
		printf(W"%-6ld"DEF" %ld is thinking\n", elapsed, philo->id);
	else if (status == DIED && !status_sim)
		printf(R"%-6ld %ld died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->simulation->print_mtx);
}
