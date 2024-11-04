/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:52:26 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/03 22:57:48 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	handle_overflow(int res, char digit, int signe)
{
	if ((res > INT_MAX / 10) || \
		(res == INT_MAX / 10 && (digit - '0') > INT_MAX % 10))
	{
		if (signe == 1)
			return (INT_MAX);
		return (INT_MIN);
	}
	return (res * 10 + (digit - '0'));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	res = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signe = -1;
		else
			signe = 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = handle_overflow(res, str[i++], signe);
	return (res * signe);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(500);
}
