/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:31:10 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/02 19:05:43 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	thinking(t_philosopher *philosopher)
{
	if (!is_dead(philosopher, 0) && !get_stop(philosopher->info))
	{
		print(philosopher, " is thinking\n");
		ft_usleep(philosopher->info->t_think);
	}
}

void	sleeping(t_philosopher *philosopher)
{
	if (!is_dead(philosopher, 0) && !get_stop(philosopher->info))
	{
		print(philosopher, " is sleeping\n");
		ft_usleep(philosopher->info->t_sleep);
	}
}

void	meal_counting(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->info->m_stop);
	philosopher->meal_count++;
	if (philosopher->meal_count == philosopher->info->n_eat)
	{
		philosopher->info->n_meals++;
		if (philosopher->info->n_meals == philosopher->info->num_philosophers)
			is_dead(philosopher, 2);
	}
	pthread_mutex_unlock(&philosopher->info->m_stop);
}

void	take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
		usleep(1000);
	if (philosopher->left_fork < philosopher->right_fork)
	{
		pthread_mutex_lock(philosopher->left_fork);
		print(philosopher, " has taken left fork\n");
		pthread_mutex_lock(philosopher->right_fork);
		print(philosopher, " has taken right fork\n");
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		print(philosopher, " has taken right fork\n");
		pthread_mutex_lock(philosopher->left_fork);
		print(philosopher, " has taken left fork\n");
	}
}

void	eating(t_philosopher *philosopher)
{
	while (!is_dead(philosopher, 0) && !get_stop(philosopher->info)
		&& (philosopher->info->n_eat == 0
			|| philosopher->meal_count < philosopher->info->n_eat))
	{
		take_forks(philosopher);
		print(philosopher, " is eating\n");
		pthread_mutex_lock(&(philosopher->info->m_eat));
		philosopher->last_meal_time = timestamp();
		pthread_mutex_unlock(&(philosopher->info->m_eat));
		ft_usleep(philosopher->info->t_eat);
		meal_counting(philosopher);
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		sleeping(philosopher);
		thinking(philosopher);
	}
}
