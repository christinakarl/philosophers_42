/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:44:01 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/15 14:56:49 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitor_philos(t_struct *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->total_philo)
		{
			if (check_if_dead_while_fork(&data->philo[i]) != 0)
				break ;
		}
	}
}

int	check_if_dead_while_fork(t_philo *philo)
{
	while (check_eat(philo) == 0)
	{
		if ((get_current_time(philo->data) - philo->last_meal \
			>= philo->data->time_to_die))
		{
			print_msg(DIE, philo);
			if (philo->l_taken == 1)
			{
				pthread_mutex_unlock((philo->l_fork));
				philo->l_taken = 1;
			}
			if (philo->r_taken == 1)
			{
				pthread_mutex_unlock((philo->r_fork));
				philo->r_taken = 0;
			}
			return (1);
		}
	}
	return (0);
}

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
