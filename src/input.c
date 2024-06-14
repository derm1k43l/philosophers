/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:20:43 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/14 13:22:49 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	input_check(t_simulation *simulation, char **av)
{
	simulation->philo_nbr = ft_atol(av[1]);
	if (simulation->philo_nbr > 200)
		error_exit(R"Max philosophers is 200, get serious!"DEF);
	simulation->time_to_eat = ft_atol(av[3]) * 1e3;
	simulation->time_to_sleep = ft_atol(av[4]) * 1e3;
	simulation->time_to_die = ft_atol(av[2]) * 1e3;
	if (simulation->time_to_eat < 6e4
		|| simulation->time_to_sleep < 6e4
		|| simulation->time_to_die < 6e4)
		error_exit("Use value for times above"G" 60ms"DEF);
	if (av[5])
		simulation->limit_meals = ft_atol(av[5]);
	else
		simulation->limit_meals = -1;
}

long	ft_atol(char *str)
{
	long	nbr;

	nbr = 0;
	str = ft_preatol(str);
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX)
		error_exit("Values exceeds INT_MAX.");
	return (nbr);
}

char	*ft_preatol(char *str)
{
	char	*nbr;
	int		l;

	l = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only positive value make sense.");
	if (*str < '0' || *str > '9')
		error_exit("The number is not correct formated.");
	nbr = str;
	while (*str >= '0' && *str <= '9')
	{
		str++;
		l++;
	}
	if (l > 10)
		error_exit("Values exceeds INT_MAX.");
	return (nbr);
}
