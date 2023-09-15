/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:28:55 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/15 14:49:25 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//all you can eat
void	philo_eat(t_philo *philo)
{
	// pthread_mutex_lock((philo->l_fork));
	// print_msg(TAKE_FORK, philo);
	// if (check_if_dead(philo) != 0 || check_if_all_finished(philo) != 0)
	// {
	// 	pthread_mutex_unlock((philo->l_fork));
	// 	return ;
	// }
	// pthread_mutex_lock((philo->r_fork));
	// print_msg(TAKE_FORK, philo);
	if (take_fork(philo) == 0)
	{
		philo->last_meal = get_current_time(philo->data);
		print_msg(EAT, philo);
		philo->meals_nbr += 1;
		ft_usleep(philo->data->time_to_eat, philo);
		change_eat(philo, 0);
		pthread_mutex_unlock((philo->l_fork));
		pthread_mutex_unlock((philo->r_fork));
		philo->l_taken = 0;
		philo->r_taken = 0;
	}
}

//sleep tight
void	philo_sleep(t_philo *philo)
{
	if (check_if_dead(philo) != 0)
		return ;
	print_msg(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep, philo);
}

//think deeply
void	philo_think(t_philo *philo)
{
	if (check_if_dead(philo) != 0)
		return ;
	print_msg(THINK, philo);
}

/*normal philo routine: handle errors, total_meals,
deaths + eat, sleep, think, repeat*/
void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->data->total_meals == 0)
		return ((void *) 1);
	while (1)
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

//routine in case total_philo=1
void	*one_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	ft_usleep(philo->data->time_to_die, philo);
	print_msg(ONLY_ONE, philo);
	return ((void *)0);
}
