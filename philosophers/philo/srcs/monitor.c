/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:02:06 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/20 12:23:55 by ckarl            ###   ########.fr       */
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

//monitor check that changes the stop value if a philo dies
int	check_if_dead_while_forking(t_philo *philo)
{
	while (check_eat(philo) == 0)
	{
		if ((get_current_time(philo->data) - check_lastmeal(philo) \
			>= philo->data->time_to_die))
		{
			print_msg(DIE, philo);
			pthread_mutex_unlock((philo->l_fork));
			pthread_mutex_unlock((philo->r_fork));
			return (1);
		}
	}
	return (0);
}


//check when the last meal was
int	check_lastmeal(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&(philo->lm_lock));
	value = philo->last_meal;
	pthread_mutex_unlock(&(philo->lm_lock));
	return (value);
}

//change the last meal time to current (while eating)
void	change_lastmeal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->lm_lock));
	philo->last_meal = get_current_time(philo->data);
	pthread_mutex_unlock(&(philo->lm_lock));
}