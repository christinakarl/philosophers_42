/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:23:41 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/13 17:56:37 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//print the received msg and change death status if necessary
void	print_msg(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&(philo->data->write_lock));
	time = get_current_time(philo->data) - philo->data->start_time;
	if (philo->data->stop == 0)
	{
		if (ft_strcmp(str, DIE) == 0)
		{
			pthread_mutex_lock(&(philo->data->stop_lock));
			philo->data->stop = 1;
			printf("%d: Philospher %d %s\n", time, philo->id, str);
			pthread_mutex_unlock(&(philo->data->stop_lock));
		}
		else if (ft_strcmp(str, FINISH) == 0 || \
				ft_strcmp(str, ONLY_ONE) == 0)
		{
			pthread_mutex_lock(&(philo->data->stop_lock));
			philo->data->stop = 1;
			printf("%d: %s\n", time, str);
			pthread_mutex_unlock(&(philo->data->stop_lock));
		}
		else
			printf("%d: Philospher %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&(philo->data->write_lock));
}

//print received error msg and clear data struct (if given)
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

//free all assigned memory and destroy mutexes
void	clear_all(t_struct *data)
{
	int	i;

	i = -1;
	if (data)
	{
		while (++i < data->total_philo)
			pthread_mutex_destroy(&data->forks[i]);
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

//get current time in milliseconds
int	get_current_time(t_struct *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (error_msg(TIME_ERR, data));
	return (((time.tv_sec) * 1000) + (time.tv_usec / 1000));
}

/*works better for shorter sleeping periods because it reduces
granularity (minimum sleep time that can be handled effectively, usually
in milliseconds) and function call overhead (set up & tear down of the
function)
>> useconds_t = microseconds = 1000 * milliseconds*/
int	ft_usleep(int milli_sleep, t_struct *data)
{
	int	start;

	if (milli_sleep == 0)
		return (0);
	start = get_current_time(data);
	while ((get_current_time(data) - start) < (milli_sleep))
		usleep(500);
	return (0);
}
