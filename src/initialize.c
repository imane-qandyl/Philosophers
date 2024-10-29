/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:44:36 by imqandyl          #+#    #+#             */
/*   Updated: 2024/10/29 14:31:44 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
void init_philosophers(t_info *info,t_philosopher *philosophers)
{
    int i;
	i = 0;
	info->t_start = timestamp();
    while (i < info->num_philosophers)
    {
        philosophers[i].id = i;
        philosophers[i].left_fork = &(info->forks[i]); // Left fork is the philosopher's own fork
        philosophers[i].right_fork = &(info->forks[(i + 1) % info->num_philosophers]); // Right fork is the next philosopher's fork
        philosophers[i].last_meal_time = info->t_start;
        philosophers[i].meal_count = 0;
        philosophers[i].info = info;
        i++;
    }
}
int	var_init(t_info *data, char **av)
{
	int i;
	i= 0;
	if (check_num(av))
	{
		printf("%sInvalid Arguments\n",RED);
		return (1);
	}
	data->num_philosophers = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5]) {
        data->n_eat = ft_atoi(av[5]);
        if (data->n_eat <= 0) {
            return 1; // n_eat must be a positive value
        }
    }
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->stop = 0;
	data->philosopher = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (data->philosopher == NULL)
		return (2);
	data->n_meals = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (data->forks == NULL) {
        printf("%sFailed to allocate memory for forks",RED);
        free(data->philosopher);
        return (2);
    }
    
    while(i < data->num_philosophers) {
        pthread_mutex_init(&data->forks[i], NULL);
		i++;
    }
    return (0);
}