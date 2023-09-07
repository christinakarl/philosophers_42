/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:24:06 by ckarl             #+#    #+#             */
/*   Updated: 2023/09/07 15:37:22 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_strcmp(char *str, char *comp)
{
	int	i;

	i = 0;
	if (!str || !comp)
		return (1);
	while (str[i] == comp[i] && str[i] != '\0' && comp[i] != '\0')
	{
		i++;
	}
	return (str[i] - comp[i]);
}

/*work better for shorter sleeping periods because it reduces
granularity (minimum sleep time that can be handled effectively, usually
in milliseconds) and function call overhead (set up & tear down of the
function)
>> useconds_t = microseconds = 1000 * milliseconds*/
int	ft_usleep(int milli_sleep, t_struct *data)
{
	int	start;

	start = get_current_time(data);
	while ((get_current_time(data) - start) < (milli_sleep * 1000))
		usleep((milli_sleep * 1000) / 10);
	return (0);
}