/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:44:01 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/14 14:11:58 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_fork(t_fork *f, t_philo *philo)
{
	int	value;

	value = 0;
	pthread_mutex_lock(f->fork);
	if (f->occupied == 0 || f->occupied == philo->id)
	{
		f->occupied = philo->id;
		print_msg(TAKE_FORK, philo);
		value = 0;
	}
	else
		value = 1;
	pthread_mutex_unlock(f->fork);
	return (value);
}

int	drop_fork(t_fork *f, t_philo *philo)
{
	int	value;

	value = 0;
	pthread_mutex_lock(f->fork);
	if (f->occupied == philo->id)
	{
		f->occupied = 0;
		value = 0;
	}
	else
		value = 1;
	pthread_mutex_unlock(f->fork);
	return (value);
}