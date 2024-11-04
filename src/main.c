/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 07:35:14 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/03 23:03:34 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->info->num_philosophers == 1)
	{
		print(philosopher, " has taken a fork\n");
		philosopher->t_start = timestamp();
		while (timestamp() - philosopher->t_start < philosopher->info->t_die)
			usleep(100);
		print(philosopher, " has died\n");
		set_stop(philosopher->info);
		return (NULL);
	}
	while (!get_stop(philosopher->info) && !is_dead(philosopher, 0))
	{
		eating(philosopher);
		if (philosopher->info->n_eat > 0 && \
			philosopher->meal_count >= philosopher->info->n_eat)
			break ;
	}
	return (NULL);
}

void	cleanup(t_info *data)
{
	int	i;

	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philosopher);
	free(data->forks);
}

void	print(t_philosopher *philosopher, char *str)
{
	long int	time;

	time = timestamp() - philosopher->t_start;
	if (!get_stop(philosopher->info) && time >= 0
		&& time <= INT_MAX && !is_dead(philosopher, 0))
	{
		pthread_mutex_lock(&(philosopher->info->m_stop));
		printf("%s%lld %d %s", GREEN,
			timestamp() - philosopher->info->t_start,
			philosopher->id + 1, str);
		pthread_mutex_unlock(&(philosopher->info->m_stop));
	}
}

static int	init_data(t_info *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("%sUsage: %s num_philosophers time_to_die time_to_eat"
			" time_to_sleep [num_times_to_eat]\n", BYELLOW, argv[0]);
		return (1);
	}
	data->num_philosophers = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_eat = 0;
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
	{
		printf("Error: Time values must be at least 60 ms\n");
		return (1);
	}
	return (var_init(data, argv));
}

int	main(int argc, char **argv)
{
	t_info		data;
	pthread_t	death_checker_thread;
	int			i;

	if (init_data(&data, argc, argv) != 0)
		return (1);
	init_philosophers(&data, data.philosopher);
	if (pthread_create(&death_checker_thread, NULL, \
	check_death, (void *)&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	i = -1;
	while (++i < data.num_philosophers)
		pthread_create(&data.philosopher[i].thread, NULL,
			philosopher_routine, (void *)&data.philosopher[i]);
	i = -1;
	while (++i < data.num_philosophers)
		pthread_join(data.philosopher[i].thread, NULL);
	pthread_join(death_checker_thread, NULL);
	cleanup(&data);
	return (0);
}
