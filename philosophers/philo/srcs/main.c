/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:26:14 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/05 16:43:24 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_struct	*data;

	//check parameters
	if (argc < 5 || argc > 6)
		return (error_msg(INPUT_ERR));
	//init structures
	if (init_philo(data, argc, argv) == 1)
		return (1);

	//init threads & start routine

	//end routine when nr reached or philo died & destroy threads

	//free memory

	return (0);
}