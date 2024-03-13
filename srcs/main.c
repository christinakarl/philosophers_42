/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:26:14 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/13 18:02:08 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	Place x philosphers around a table
	with one bowl of spaghetti in the middle,
	x amount of forks between them
	and a routine of eating, sleeping, thinking, repeating.

	Until someone dies of starvation (surpassed indicated time
	between two meals), everyone finished their max amount of
	meals or some other special case.

	Enjoy the party!
*/
int	main(int argc, char **argv)
{
	t_struct	data;

	if (argc < 5 || argc > 6)
		return (error_msg(INPUT_ERR, NULL));
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (allocate_memory(&data) != 0)
		return (1);
	init_philos(&data);
	if (run_threads(&data) != 0)
		return (1);
	clear_all(&data);
	return (0);
}