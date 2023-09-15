/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:02:06 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/15 18:03:43 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//monitor loop outside of threads checking for deaths due to starvation
void	monitor_philos(t_struct *data)
{
	int	i;

	i = 0;
	while (i < data->total_philo)
	{
		if (check_if_dead_while_forking(&data->philo[i]) != 0)
			break ;
		i++;
		if (i == data->total_philo)
			i = 0;
	}
}

//monitor check that changes the stop value if one dies
int	check_if_dead_while_forking(t_philo *philo)
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
				philo->l_taken = 0;
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
