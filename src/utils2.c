/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:04:17 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/04 18:59:05 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_dead(t_philosopher *philosopher, int nb)
{
	int	result;

	pthread_mutex_lock(&philosopher->info->m_stop);
	if (nb)
		philosopher->info->stop = 1;
	result = philosopher->info->stop;
	pthread_mutex_unlock(&philosopher->info->m_stop);
	return (result);
}

void	*check_death(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (!get_stop(info))
	{
		i = 0;
		while (i < info->number_of_philosophers)
		{
			pthread_mutex_lock(&info->m_eat);
			if (timestamp() - info->philosopher[i].last_meal_time > \
			info->time_to_die)
			{
				print(&info->philosopher[i], " has died\n");
				set_stop(info);
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

void	set_stop(t_info *info)
{
	pthread_mutex_lock(&info->m_stop);
	info->stop = 1;
	pthread_mutex_unlock(&info->m_stop);
}
