/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:42:37 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/20 12:10:08 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//init general data structure with the given argv parameters
int	init_data(t_struct *data, int argc, char **argv)
{
	if (check_input(argv) == 1)
		return (error_msg(INPUT_FORMAT, NULL));
	data->total_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->total_meals = ft_atoi(argv[5]);
	else
		data->total_meals = -1;
	if (data->total_philo <= 0 || data->total_philo > 200)
		return (error_msg(INPUT_PHILO, NULL));
	data->stop = 0;
	data->finished = 0;
	pthread_mutex_init(&data->stop_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	return (0);
}

//allocate memory for philo, thread and fork arrays
int	allocate_memory(t_struct *data)
{
	data->threads = malloc(sizeof(pthread_t) * data->total_philo);
	if (!data->threads)
		return (error_msg(ALLOC_ERR, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->total_philo);
	if (!data->forks)
		return (error_msg(ALLOC_ERR, data));
	data->philo = malloc(sizeof(t_philo) * data->total_philo);
	if (!data->philo)
		return (error_msg(ALLOC_ERR, data));
	return (0);
}

//init mutexes for all forks, init each philo, assign forks
void	init_philos(t_struct *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->total_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_nbr = 0;
		data->philo[i].last_meal = get_current_time(data);
		data->philo[i].data = data;
		data->philo[i].l_taken = 0;
		data->philo[i].r_taken = 0;
		data->philo[i].is_eating = 0;
		pthread_mutex_init(&data->philo[i].eat_lock, NULL);
		pthread_mutex_init(&data->philo[i].lm_lock, NULL);
		data->philo[i].r_fork = &data->forks[i];
		if (i == 0)
			data->philo[i].l_fork = &data->forks[data->total_philo - 1];
		else
			data->philo[i].l_fork = &data->forks[i - 1];
	}
}

//create threads, assign routine to each philo, join threads
int	run_threads(t_struct *data)
{
	int	i;

	i = -1;
	data->start_time = get_current_time(data);
	if (data->total_philo == 1)
		return (run_one_thread(data));
	while (++i < data->total_philo)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, \
			&data->philo[i]) != 0)
			return (error_msg(CREATE_ERR, data));
		usleep(100);
	}
	monitor_philos(data);
	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (error_msg(JOIN_ERR, data));
	}
	if (data->total_meals == 0)
		return (error_msg(FINISH_ZERO, data));
	return (0);
}

//case of total_philo=1, run one_routine
int	run_one_thread(t_struct *data)
{
	if (pthread_create(&data->threads[0], NULL, &one_routine, \
		&data->philo[0]) != 0)
		return (error_msg(CREATE_ERR, data));
	if (pthread_join(data->threads[0], NULL) != 0)
		return (error_msg(JOIN_ERR, data));
	return (0);
}
