/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:51:54 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/13 17:15:38 by ckarl            ###   ########.fr       */
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
	if (philo->data->stop != 0)
		return (1);
	else if ((get_current_time(philo->data) - philo->last_meal\
		>= philo->data->time_to_die))
	{
		print_msg(DIE, philo);
		return (1);
	}
	return (0);
}

//check if all philos finished their meals (if parameter indicated)
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
