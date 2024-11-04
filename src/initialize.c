/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:44:36 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/04 18:58:28 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philosophers(t_info *info, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	info->t_start = timestamp();
	while (i < info->number_of_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = &(info->forks[i]);
		philosophers[i].right_fork = &(info->forks[(i + 1) % \
		info->number_of_philosophers]);
		philosophers[i].last_meal_time = info->t_start;
		philosophers[i].meal_count = 0;
		philosophers[i].info = info;
		philosophers[i].number_of_philosophers = info->number_of_philosophers;
		philosophers[i].t_start = info->t_start;
		i++;
	}
}

static int	init_mutexes_and_memory(t_info *data)
{
	int	i;

	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	data->stop = 0;
	data->n_meals = 0;
	data->philosopher = malloc(sizeof(t_philosopher) * \
	data->number_of_philosophers);
	if (data->philosopher == NULL)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * \
	data->number_of_philosophers);
	if (data->forks == NULL)
	{
		printf("%s Failed to allocate memory for forks", RED);
		free(data->philosopher);
		return (1);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

static int	validate_input(t_info *data, char **av)
{
	if (check_num(av))
	{
		printf("%s Invalid Arguments\n", RED);
		return (1);
	}
	data->number_of_philosophers = ft_atoi(av[1]);
	if (data->number_of_philosophers <= 0 || data->number_of_philosophers \
	> MAX_PHILOSOPHERS)
	{
		printf("%s Error: Number of philosophers must be between 1 and %d\n",
			RED, MAX_PHILOSOPHERS);
		return (1);
	}
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_die <= 0 || data->time_to_die > INT_MAX
		|| data->time_to_eat <= 0 || data->time_to_eat > INT_MAX
		|| data->time_to_sleep <= 0 || data->time_to_sleep > INT_MAX)
	{
		printf("%s Error: Time values must be positive\n", RED);
		return (1);
	}
	return (0);
}

static int	validate_meals(t_info *data, char **av)
{
	if (av[5])
	{
		data->n_eat = ft_atoi(av[5]);
		if (data->n_eat <= 0 || data->n_eat > INT_MAX)
		{
			printf("%s Error: n_eat must be positive and within range\n", RED);
			return (1);
		}
	}
	return (0);
}

int	var_init(t_info *data, char **av)
{
	if (validate_input(data, av))
		return (1);
	if (validate_meals(data, av))
		return (1);
	return (init_mutexes_and_memory(data));
}
