/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:51:54 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/15 12:43:08 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//check if input parameters are +integers
int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' )
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//check if philo died because of starvation
int	check_if_dead(t_philo *philo)
{
	if (check_stop(philo->data) != 0)
		return (1);
	else if ((get_current_time(philo->data) - philo->last_meal \
		>= philo->data->time_to_die))
	{
		print_msg(DIE, philo);
		return (1);
	}
	return (0);
}

//check if all philos finished their meals (if parameter is indicated)
int	check_if_all_finished(t_philo *philo)
{
	if (philo->data->total_meals < 0)
		return (0);
	else if (philo->data->finished == philo->data->total_philo)
	{
		print_msg(FINISH, philo);
		return (1);
	}
	return (0);
}

int	check_stop(t_struct *data)
{
	int	value;

	pthread_mutex_lock(&(data->stop_lock));
	value = data->stop;
	pthread_mutex_unlock(&(data->stop_lock));
	return (value);
}

void	change_stop(t_struct *data)
{
	pthread_mutex_lock(&(data->stop_lock));
	data->stop = 1;
	pthread_mutex_unlock(&(data->stop_lock));
}

int	check_eat(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&(philo->eat_lock));
	value = philo->is_eating;
	pthread_mutex_unlock(&(philo->eat_lock));
	return (value);
}

void	change_eat(t_philo *philo, int index)
{
	pthread_mutex_lock(&(philo->eat_lock));
	philo->is_eating = index;
	pthread_mutex_unlock(&(philo->eat_lock));
}
