/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:20:43 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/26 12:42:51 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_clean(t_simulation *simulation, const char *error_msg)
{
	printf(RED "%s\n" RESET, error_msg);
	clean(simulation);
	return (1);
}

int	input_check(t_simulation *simulation, char **av)
{
	simulation->philo_nbr = ft_atol(av[1]);
	if (simulation->philo_nbr > 200 || simulation->philo_nbr <= 0)
	{
		printf(RED"Max philosophers is 200, get serious!\n"RESET);
		return (1);
	}
	simulation->time_to_eat = ft_atol(av[3]) * 1000;
	simulation->time_to_sleep = ft_atol(av[4]) * 1000;
	simulation->time_to_die = ft_atol(av[2]) * 1000;
	if (simulation->time_to_eat < 60000
		|| simulation->time_to_sleep < 60000
		|| simulation->time_to_die < 60000)
	{
		printf(RED"Use value for times above"GREEN" 60ms\n"RESET);
		return (1);
	}
	if (av[5])
		simulation->limit_meals = ft_atol(av[5]);
	else
		simulation->limit_meals = -1;
	return (0);
}

long	ft_atol(char *str)
{
	long	nbr;
	char	*validated_str;

	validated_str = ft_preatol(str);
	if (!validated_str)
		return (-1);
	nbr = 0;
	str = validated_str;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX)
	{
		return (-1);
	}
	return (nbr);
}

char	*ft_preatol(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (NULL);
	}
	if (*str < '0' || *str > '9')
	{
		return (NULL);
	}
	return (str);
}
