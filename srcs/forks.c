/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:44:01 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/15 18:12:02 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//taking both forks if philo didn't die before
int	take_fork(t_philo *philo)
{
	if (check_stop(philo->data) == 0)
	{
		if (philo->l_taken == 0)
		{
			pthread_mutex_lock((philo->l_fork));
			philo->l_taken = 1;
			print_msg(TAKE_FORK, philo);
		}
		if (philo->r_taken == 0)
		{
			pthread_mutex_lock((philo->r_fork));
			philo->r_taken = 1;
			print_msg(TAKE_FORK, philo);
			change_eat(philo, 1);
			return (0);
		}
	}
	return (1);
}

//check if philo is currently eating
int	check_eat(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&(philo->eat_lock));
	value = philo->is_eating;
	pthread_mutex_unlock(&(philo->eat_lock));
	return (value);
}

//indicate if philo is eating (1) or has finished eating (0)
void	change_eat(t_philo *philo, int index)
{
	pthread_mutex_lock(&(philo->eat_lock));
	philo->is_eating = index;
	pthread_mutex_unlock(&(philo->eat_lock));
}
