/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:26:14 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/11 15:25:56 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_struct	data;

	//check parameters
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd(INPUT_ERR, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	//init structures
	if (init_data(&data, argc, argv) != 0)
		return (1);

	if (allocate_memory(&data) != 0)
		return (1);
	init_philos(&data);
	//insert case if only 1 or 0 philos

	//init threads & start routine
	if (run_threads(&data) != 0)
		return (1);
	//free memory & detach threads
	clear_all(&data);
	return (0);
}