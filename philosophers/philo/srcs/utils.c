/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:23:41 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/05 17:42:27 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_msg(char *str)
{
	if (!str)
		return (1);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
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
}
