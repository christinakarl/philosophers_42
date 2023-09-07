/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:13:00 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/07 15:37:36 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

//philo msg
# define TAKE_FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIE "died"
# define FINISH "all philosphers finished their meals"
//alloc error
# define ALLOC_ERR "allocation error"
//input error
# define INPUT_ERR "please enter max 5 valid input parameters: ./philo [nr of philosophers] \
[time to die] [time to eat] [time to sleep] \
[*optional: nr of times a philospher must eat]"
# define INPUT_FORMAT "please enter positive integers (without any signs) as input parameters"
# define INPUT_PHILO "please enter between 1 and 200 as a first parameter"
//thread error
# define CREATE_ERR "pthread_create() error"
# define JOIN_ERR "pthread_join() error"
//time error
# define TIME_ERR "could not retrieve time of day"
//philo is doing
# define N	0
# define E	1
# define S	2
# define T	3

struct s_struct;

typedef struct s_philo
{
	struct s_struct	*data;
	int				id;
	int				meals_nbr;
	int				is_doing;
	int				last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_struct
{
	pthread_t		*threads;
	t_philo			*philo;
	int				total_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				finished;
	int				stop;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	write_lock;
}	t_struct;

/*	utils.c	*/
int		error_msg(char *str, t_struct *data);
int		input_checker(char **argv);
int		get_current_time(t_struct *data);
void	clear_all(t_struct *data);
void	print_msg(char *str, t_philo *philo);

/*	helpers.c	*/
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(char *str, char *comp);
int		ft_usleep(int milli_sleep, t_struct *data);

/*	init.c	*/
int		init_data(t_struct *data, int argc, char **argv);
int		allocate_memory(t_struct *data);
void	init_philos(t_struct *data);
int		run_threads(t_struct *data);

/*	routine.c	*/
void	*routine(void *p);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif