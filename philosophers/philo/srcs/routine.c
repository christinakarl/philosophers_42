/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:28:55 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/13 17:40:18 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*in order to be passed to pthread_create, this function
needs to return a (void *) and can only take a (void *)
argument which can then be typecasted to what we are passing*/

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock((philo->l_fork));
	print_msg(TAKE_FORK, philo);
	if (check_if_dead(philo) != 0 || check_if_all_finished(philo) != 0)
	{
		pthread_mutex_unlock((philo->l_fork));
		return ;
	}
	pthread_mutex_lock((philo->r_fork));
	print_msg(TAKE_FORK, philo);
	if (philo->data->stop == 0)
	{
		philo->last_meal = get_current_time(philo->data);
		print_msg(EAT, philo);
		philo->meals_nbr += 1;
		ft_usleep(philo->data->time_to_eat, philo->data);
	}
	pthread_mutex_unlock((philo->l_fork));
	pthread_mutex_unlock((philo->r_fork));
}

void	philo_sleep(t_philo *philo)
{
	if (check_if_dead(philo) != 0)
		return ;
	print_msg(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	if (check_if_dead(philo) != 0)
		return ;
	print_msg(THINK, philo);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->data->total_meals == 0)
		return ((void *) 1);
	while (philo->data->stop == 0)
	{
		if (check_if_dead(philo) != 0)
			break ;
		philo_eat(philo);
		if (philo->meals_nbr == philo->data->total_meals)
		{
			pthread_mutex_lock(&(philo->data->meals_lock));
			philo->data->finished += 1;
			if (check_if_all_finished(philo) != 0)
			{
				pthread_mutex_unlock(&(philo->data->meals_lock));
				break ;
			}
			pthread_mutex_unlock(&(philo->data->meals_lock));
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return ((void *)0);
}

void	*one_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	print_msg(ONLY_ONE, philo);
	return ((void *)0);
}
