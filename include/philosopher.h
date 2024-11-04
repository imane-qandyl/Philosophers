/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:11:48 by imqandyl          #+#    #+#             */
/*   Updated: 2024/11/04 18:58:05 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define MAX_PHILOSOPHERS 200
# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eating_time;
	int				meal_count;
	long long		last_meal_time;
	struct s_info	*info;
	int				number_of_philosophers;
	long int		t_start;
}	t_philosopher;

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				t_think;
	int				stop;
	long int		t_start;
	int				n_meals;
	int				n_eat;
	t_philosopher	*philosopher;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	*forks;
}	t_info;

void		*philosopher_routine(void *arg);
int			ft_isdigit(int character);
int			ft_atoi(const char *str);
int			check_num(char **str);
void		thinking(t_philosopher *philosopher);
void		sleeping(t_philosopher *philosopher);
void		meal_counting(t_philosopher *philosopher);
void		init_philosophers(t_info *info, t_philosopher *philosophers);
long long	timestamp(void);
void		ft_usleep(int ms);
int			var_init(t_info *data, char **av);
void		*check_death(void *arg);
void		print(t_philosopher *philosopher, char *str);
int			is_dead(t_philosopher *philosopher, int nb);
void		meal_counting(t_philosopher *philosopher);
void		eating(t_philosopher *philosopher);
int			get_stop(t_info *info);
void		cleanup(t_info *data);
void		take_forks(t_philosopher *philosopher);
void		set_stop(t_info *info);

#endif
