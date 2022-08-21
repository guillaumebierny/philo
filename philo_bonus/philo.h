/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:22:43 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/18 03:56:22 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <signal.h>

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
    pid_t pid;
    atomic_int resting_time;
	struct s_state *state;
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
    sem_t sem_write;
    sem_t sem_fork;
    sem_t sem_finish;
    sem_t meal;
}		t_state;


int    display_message(t_philo *philo, char *s, int n);
void *check_death(void *philo);
void	*check_last_meal(void *state_v);
int	take_fork(t_philo *philo);
int	eat(t_philo *philo);
int	sleep_think(t_philo *philo);
int	initialise_v(t_state *s, char **argv, int argc);
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