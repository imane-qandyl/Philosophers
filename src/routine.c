/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:31:10 by imqandyl          #+#    #+#             */
/*   Updated: 2024/10/29 14:26:32 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


    // Think
void    thinking(t_philosopher *philosopher)
{
   if (!is_dead(philosopher, 0) && !philosopher->info->stop) {
        print(philosopher, " is thinking\n");
        ft_usleep(philosopher->info->t_think); // Or use different duration for thinking if needed
    }
}
    
void	sleeping(t_philosopher *philosopher)
{
	if (!is_dead(philosopher, 0) && !philosopher->info->stop) {
        print(philosopher, " is sleeping\n");
        ft_usleep(philosopher->info->t_sleep);
    }
}
void *check_death(void *arg) {
    t_info *info = (t_info *)arg;
    int i = 0;
    while (!info->stop) {
        i = 0; 
       while(i < info->num_philosophers) {
            pthread_mutex_lock(&info->m_eat);
            long long time_since_last_meal = timestamp() - info->philosopher[i].last_meal_time;
            pthread_mutex_unlock(&info->m_eat);

            if (time_since_last_meal > info->t_die) {
                print(&info->philosopher[i], " has died\n");
                pthread_mutex_lock(&info->m_stop);
                info->stop = 1; // Stop the simulation
                pthread_mutex_unlock(&info->m_stop);
                return NULL;
            }
            i++;
        }
        usleep(100); // Sleep to avoid busy waiting
    }
    return NULL;
}
void	meal_counting(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->info->m_stop);
	philosopher->meal_count++;
	if (philosopher->meal_count == philosopher->info->n_eat)
	{
		philosopher->info->n_meals++;
		if (philosopher->info->n_meals == philosopher->info->num_philosophers)
		{
			is_dead(philosopher, 2);  // Signal to stop the simulation if all philosophers have eaten
		}
	}
	pthread_mutex_unlock(&philosopher->info->m_stop);
}
void eating(t_philosopher *philosopher) {
    while (!is_dead(philosopher, 0)&& !philosopher->info->stop && 
           (philosopher->info->n_eat == 0 || philosopher->meal_count < philosopher->info->n_eat)) 
    {
    if (philosopher->id % 2 == 0) {
        pthread_mutex_lock(philosopher->left_fork);
        print(philosopher, " has taken left fork\n");

        pthread_mutex_lock(philosopher->right_fork);
        print(philosopher, " has taken right fork\n");
    } 
    else {
        pthread_mutex_lock(philosopher->right_fork);
        print(philosopher, " has taken right fork\n");

        pthread_mutex_lock(philosopher->left_fork);
        print(philosopher, " has taken left fork\n");
    }

    // Philosopher starts eating
    print(philosopher, " is eating\n");
    pthread_mutex_lock(&(philosopher->info->m_eat));
    philosopher->last_meal_time = timestamp();
    pthread_mutex_unlock(&(philosopher->info->m_eat));

    ft_usleep(philosopher->info->t_eat);  // Simulate eating time

    // Update meal count
    meal_counting(philosopher);

    // Release the forks after eating
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
    sleeping(philosopher); 
    thinking(philosopher);
    }
}