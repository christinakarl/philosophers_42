/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:28:55 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/11 14:18:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*in order to be passed to pthread_create, this function
needs to return a (void *) and can only take a (void *)
argument which can then be typecasted to what we are passing*/

void	philo_eat(t_philo *philo)
{
	if (philo->data->stop == 1)
		return ;
	pthread_mutex_lock((philo->l_fork));
	pthread_mutex_lock((philo->r_fork));
	print_msg(TAKE_FORK, philo);
	print_msg(TAKE_FORK, philo);
	philo->is_doing = E;
	philo->last_meal = get_current_time(philo->data);
	print_msg(EAT, philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	philo->meals_nbr += 1;
	if (philo->meals_nbr == philo->data->total_meals)
	{
		pthread_mutex_lock(&(philo->data->meals_lock));
		philo->data->finished += 1;
		pthread_mutex_unlock(&(philo->data->meals_lock));
	}
	pthread_mutex_unlock((philo->l_fork));
	pthread_mutex_unlock((philo->r_fork));
}

void	philo_sleep(t_philo *philo)
{
	if (philo->data->stop == 1)
		return ;
	philo->is_doing = S;
	print_msg(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	if (philo->data->stop == 1)
		return ;
	philo->is_doing = T;
	print_msg(THINK, philo);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->data->stop == 0)
	{
		printf("beginning of loop in routine %d\n", philo->id);
		if (philo->data->finished == philo->data->total_meals)
		{
			print_msg(FINISH, philo);
		}
		if ((philo->last_meal + philo->data->time_to_die) \
			< get_current_time(philo->data) && philo->is_doing != E)
			print_msg(DIE, philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}

void	*test_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	printf("created philo %d\n", philo->id);
	while (philo->data->stop ==0)
		printf("data == 0\n");
	return ((void *)0);
}


