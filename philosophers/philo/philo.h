/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:13:00 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/05 17:29:27 by ckarl            ###   ########.fr       */
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
//alloc error
# define ALLOC_ERR "allocation error"
//input error
# define INPUT_ERR "please enter max 5 valid input parameters: ./philo [nr of philosophers] \
					[time to die] [time to eat] [time to sleep] \
					[*optional: nr of times a philospher must eat]"
# define INPUT_FORMAT "please enter only positive integers as input parameters"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	// int				eating;
	uint64_t		last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_struct
{
	pthread_t		*t;
	int				total_philo;
	int				dead;
	// int				finished;
	t_philo			*philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_nbr;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_struct;

/*	utils.c	*/
int		error_msg(char *str);
int		input_checker(char **argv);

/*	helpers.c	*/
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);


#endif