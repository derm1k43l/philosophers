/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:47:35 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/14 13:39:01 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Standard
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

// Colors
# define R "\033[1;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define B "\033[0;34m"
# define W "\033[0;37m"
# define DEF "\033[m"

// Typdef
typedef pthread_mutex_t	t_mtx;

// Forward declaration of structs
typedef struct s_philo	t_philo;

// **********************====ENUM====*********************
// code for philo status
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED,
}	t_status;

// code for time
typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time;

// **********************====STRUCT====*********************
// Strucutre for simulation enviroment
typedef struct s_simulation
{
	uint8_t		philo_nbr;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		limit_meals;
	long		start_time;
	uint8_t		threads_running_nbr;
	bool		simulation_running;
	bool		sync_ready;
	t_mtx		sim_mutex;
	t_mtx		print_mtx;
	t_mtx		*forks;
	t_philo		*philosophers;
	pthread_t	monitor;
}	t_simulation;

// Strucutre for Philosophers atributes
typedef struct s_philo
{
	uint8_t			id;
	long			last_meal_time;
	int				meals_index;
	bool			full;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
	t_mtx			philo_mutex;
	pthread_t		id_thread;
	t_simulation	*simulation;
}	t_philo;

// **********************====FUNCTION DECLARATION====*********************
// main.c
void	*monitoring_dinner(void *data);

// utils.c
void	*ft_malloc(size_t bytes);
void	clean(t_simulation *simulation);
long	ft_gettime(t_time code);
void	ft_usleep(t_simulation *simulation, long usecond);
void	print_status(t_philo *philo, t_status status);

// input.c
void	input_check(t_simulation *simulation, char **av);
char	*ft_preatol(char *str);
long	ft_atol(char *str);

// data.c
void	data_init(t_simulation *simulation);
void	philo_init(t_simulation *simulation);
void	assign_forks(t_philo *philo, t_mtx *forks);

// error.c
void	error_exit(const char *error);
bool	philo_died(t_philo *philo);

// simulation0.c
void	start_simulation(t_simulation *simulation);
void	*dinner_routine(void *data);
void	eat(t_philo *philo);
void	*unus_philosophus(void *arg);

// simulation1.c
void	wait_sync(t_simulation *simulation);
void	desync(t_philo *philo);
bool	simulation_status(t_simulation *simulation);

#endif
