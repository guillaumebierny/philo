#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdatomic.h>

enum
{
	CASE_EAT = 0,
	CASE_SLEEP = 1,
	CASE_DEAD = 2,
	CASE_THINK = 3,
	CASE_FORK = 4
};

struct s_state;

typedef struct s_philo
{
    int p_place;
    int is_eating;
    int is_sleeping;
	int resting_meal;
    atomic_int resting_time;
	struct s_state *state;
    pthread_mutex_t eat_m;
    pthread_mutex_t temps;
}					t_philo;

typedef struct s_state
{
    int n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
	int	n_of_meal;
    int start;
    t_philo *philo;
    pthread_mutex_t write;
    pthread_mutex_t *fork;
    atomic_bool end;
    pthread_mutex_t finish;
}		t_state;


int    display_message(t_philo *philo, char *s, int n);
void *check_death(void *philo);
void	*check_last_meal(void *state_v);
int	take_fork(t_philo *philo);
int	eat(t_philo *philo);
int	sleep_think(t_philo *philo);
int	init(t_state *s, char **argv, int argc);
void	*philos_routine(void *philo_var);
void    ft_putnbr(int n);
size_t  ft_strlen(char *s);
void ft_putstr(char *s);
int get_time(void);
int    ft_atoi(char *str);
int error_message(char *s);
void    my_usleep(unsigned int n);
void	f_unlock(t_state *s);

#endif