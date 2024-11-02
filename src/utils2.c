/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:04:17 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/02 21:58:58 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		usleep(ms / 10);
}

int	is_dead(t_philosopher *philosopher, int nb)
{
	pthread_mutex_lock(&philosopher->info->dead);
	if (nb)
		philosopher->info->stop = 1;
	if (philosopher->info->stop)
	{
		pthread_mutex_unlock(&philosopher->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->info->dead);
	return (0);
}

void	*check_death(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (!get_stop(info))
	{
		i = 0;
		while (i < info->num_philosophers)
		{
			pthread_mutex_lock(&info->m_eat);
			if (timestamp() - info->philosopher[i].last_meal_time > info->t_die)
			{
				print(&info->philosopher[i], " has died\n");
				pthread_mutex_lock(&info->m_stop);
				info->stop = 1;
				pthread_mutex_unlock(&info->m_stop);
				pthread_mutex_unlock(&info->m_eat);
				return (NULL);
			}
			pthread_mutex_unlock(&info->m_eat);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	get_stop(t_info *info)
{
	int	stop;

	pthread_mutex_lock(&info->m_stop);
	stop = info->stop;
	pthread_mutex_unlock(&info->m_stop);
	return (stop);
}
