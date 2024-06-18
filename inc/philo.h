/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:47:35 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/18 14:38:37 by mrusu            ###   ########.fr       */
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
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

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
	short		philo_nbr;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		limit_meals;
	long		start_time;
	short		threads_running_nbr;
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
	short			id;
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
void	error_exit(const char *error);
void	input_check(t_simulation *simulation, char **av);
char	*ft_preatol(char *str);
long	ft_atol(char *str);

// data.c
void	data_init(t_simulation *simulation);
void	philo_init(t_simulation *simulation);
void	assign_forks(t_philo *philo, t_mtx *forks);

// simulation0.c
void	start_simulation(t_simulation *simulation);
void	*dinner_routine(void *data);
void	eat(t_philo *philo);
void	*unus_philosophus(void *arg);
bool	philo_died(t_philo *philo);

// simulation1.c
void	wait_sync(t_simulation *simulation);
void	desync(t_philo *philo);
bool	get_simulation_status(t_simulation *simulation);
bool	all_threads_active(t_mtx *mtx, short *threads, short philo_nbr);
void	increase_threads_running(t_simulation *simulation);

// helper_func.c
void	set_simulation(t_simulation *simulation, bool status);
void	set_sync(t_simulation *simulation, bool status);
void	set_last_meal_time(t_philo *philo, long time);
long	get_last_meal_time(t_philo *philo);
void	increment_meals_index(t_philo *philo);
bool	is_philo_full(t_philo *philo);

#endif
