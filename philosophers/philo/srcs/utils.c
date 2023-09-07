/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:23:41 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/07 15:41:02 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_msg(char *str, t_struct *data)
{
	if (!str)
		return (1);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (data)
		clear_all(data);
	return (1);
}

int	input_checker(char **argv)
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

//get current time in milliseconds
int	get_current_time(t_struct *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 1)
		return (error_msg(TIME_ERR, data));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

//free all assigned memory and destroy mutexes
void	clear_all(t_struct *data)
{
	int	i;

	i = -1;
	if (data)
	{
		while (++i < data->total_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philo[i].lock);
		}
		if (data->philo)
			free(data->philo);
		if (data->threads)
			free(data->threads);
		if (data->forks)
			free(data->forks);
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->stop_lock);
		pthread_mutex_destroy(&data->meals_lock);
	}
}

void	print_msg(char *str, t_philo *philo)
{
	int	time;
	pthread_mutex_lock(&(philo->data->write_lock));
	time = get_current_time(philo->data) - philo->data->start_time;
	if (ft_strcmp(str, DIE) == 0)
	{
		pthread_mutex_lock(&(philo->data->stop_lock));
		philo->data->stop = 1;
		printf("%d: philospher %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&(philo->data->stop_lock));
	}
	else if (ft_strcmp(str, FINISH) == 0)
	{
		pthread_mutex_lock(&(philo->data->stop_lock));
		philo->data->stop = 1;
		printf("%d: %s\n", time, str);
		pthread_mutex_unlock(&(philo->data->stop_lock));
	}
	else
		printf("%d: philospher %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&(philo->data->write_lock));
}