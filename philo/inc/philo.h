/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:47:35 by mrusu             #+#    #+#             */
/*   Updated: 2024/06/29 12:20:56 by mrusu            ###   ########.fr       */
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
	int				index;
}	t_philo;

// **********************====FUNCTION DECLARATION====*********************
// main.c
void	*monitor(void *data);

// utils.c
void	*ft_malloc(size_t bytes);
void	clean(t_simulation *simulation);
long	ft_gettime(t_time code);
void	ft_usleep(t_simulation *simulation, long usecond);
void	print_status(t_philo *philo, t_status status);

// input.c
int		error_clean(t_simulation *simulation, const char *error_msg);
int		input_check(t_simulation *simulation, char **av);
char	*ft_preatol(char *str);
long	ft_atol(char *str);

// data.c
int		data_init(t_simulation *simulation);
int		philo_init(t_simulation *simulation);
void	assign_forks(t_philo *philo, t_mtx *forks);
void	forks_lock(t_philo *philo);

// simulation0.c
int		start_simulation(t_simulation *simulation);
void	*dinner_routine(void *data);
void	eat(t_philo *philo);
void	*unus_philosophus(void *arg);
int		create_threads(t_simulation *simulation, int *index);

// simulation1.c
void	wait_sync(t_simulation *simulation);
bool	all_threads_active(t_mtx *mtx, short *threads, short philo_nbr);
bool	philo_died(t_philo *philo);
bool	all_philos_full(t_simulation *simulation);

// helper_func.c
void	set_last_meal_time(t_philo *philo);
long	get_last_meal_time(t_philo *philo);
bool	get_status(t_mtx *mutex, bool *status);
void	set_status(t_mtx *mutex, bool *dst, bool status);
void	increase_threads_running(t_simulation *simulation);

#endif
