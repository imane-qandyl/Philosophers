#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#define MAX_PHILOSOPHERS 200
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

#include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philosopher {
    int id;                     
    pthread_t thread;            
    pthread_mutex_t *left_fork;  
    pthread_mutex_t *right_fork; 
	int			eating_time;
    int             meal_count;
    long long last_meal_time;
    struct  s_info          *info;
} t_philosopher;

typedef struct s_info {
    int                     num_philosophers;
    int t_die;
    int t_eat;
    int t_sleep;
    int t_think;
    int stop;
    long int		t_start;
    int n_meals;               // Optional: how many meals each philosopher must eat
    int n_eat;
    t_philosopher	*philosopher;
    pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
    pthread_mutex_t *forks;
} t_info;
void *philosopher_routine(void *arg);
int			ft_isdigit(int character);
int			ft_atoi(const char *str);
int	        check_num(char **str);
void        thinking(t_philosopher *philosopher);
void	    sleeping(t_philosopher *philosopher);
void	meal_counting(t_philosopher *philosopher);
void init_philosophers(t_info *info,t_philosopher *philosophers);
long long	timestamp(void);
void	    ft_usleep(int ms);
int	        var_init(t_info *data, char **av);
void    *check_death(void *arg);
void	print(t_philosopher *philosopher, char *str);
int	is_dead(t_philosopher *philosopher, int nb);
void	meal_counting(t_philosopher *philosopher);
void eating(t_philosopher *philosopher);


#endif
