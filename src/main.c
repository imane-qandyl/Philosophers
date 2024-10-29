/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:35:14 by imqandyl          #+#    #+#             */
/*   Updated: 2024/10/29 14:35:00 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philosopher_routine(void *arg)
{
   t_philosopher *philosopher = (t_philosopher *)arg;
   if (philosopher->info->num_philosophers == 1) {
        usleep(philosopher->info->t_die * 1000);
        print(philosopher, "has died");
        philosopher->info->stop = 1;
        return NULL;
    }
    while (!philosopher->info->stop) {
        eating(philosopher);
        if (is_dead(philosopher, 0))
            break;
    }

    return NULL;
}
void	print(t_philosopher *philosopher, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philosopher->info->print));
	time = timestamp() - philosopher->info->t_start;//how long the simulation has been running.
	if (!philosopher->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philosopher, 0))
		printf("%s%lld %d %s",GREEN, timestamp() - philosopher->info->t_start, philosopher->id, str);
	pthread_mutex_unlock(&(philosopher->info->print));
}

int main(int argc, char **argv)
{
    t_info data;
    pthread_t death_checker_thread;
    int i = 0;
    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "%sUsage: %s num_philosophers time_to_die time_to_eat time_to_sleep [num_times_to_eat]\n",BYELLOW, argv[0]);
        return 1;
    }

    // // Initialize philosopher information
    data.num_philosophers = ft_atoi(argv[1]);
    data.t_die = ft_atoi(argv[2]);
    data.t_eat = ft_atoi(argv[3]);
    data.t_sleep = ft_atoi(argv[4]);

    if (var_init(&data, argv) != 0)
        return 1;

    init_philosophers(&data, data.philosopher);

    pthread_create(&death_checker_thread, NULL, check_death, (void *)&data);
    
   while(i < data.num_philosophers)
    {
        pthread_create(&data.philosopher[i].thread, NULL, philosopher_routine, (void *)&data.philosopher[i]);
        printf("Philosopher %d created\n", i);
        i++;
    }
    i = 0;
    while(i < data.num_philosophers)
    {
        pthread_join(data.philosopher[i].thread, NULL);
        i++;
    }
    pthread_join(death_checker_thread, NULL);
    // Destroy mutexes before freeing memory
    pthread_mutex_destroy(&data.print);
    pthread_mutex_destroy(&data.m_stop);
    pthread_mutex_destroy(&data.m_eat);
    pthread_mutex_destroy(&data.dead);
    i = 0;
    while(i < data.num_philosophers) {
        pthread_mutex_destroy(&data.forks[i]);
        i++;
    }
    free(data.philosopher);
    free(data.forks);
    return 0;
}
