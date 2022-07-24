#ifndef PHILO_H
# define PHILO_H
# include <time.h>
# include <pthread.h>

enum
{
	CASE_EAT = 0,
	CASE_SLEEP = 1,
	CASE_DEAD = 2,
	CASE_THINK = 3,
	CASE_FORK = 4
};

typedef struct s_philo
{
    int p_place;
    int is_eating;
    int is_sleeping;
    int starting_point;
	int resting_meal;
	t_state *state;
    pthread_mutex_t write;
    int lfork;
    int rfork;
}					t_philo;

typedef struct s_state
{
    int n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
	int	n_of_meal;
    t_philo *philo;
    pthread_mutex_t dead_m;
    pthread_mutex_t fork;

}		t_state;

#endif