/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:55:14 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/08 15:04:56 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_message(t_philo *philo, char *s, int n)
{
	pthread_mutex_lock(&philo->state->write);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&philo->state->write);
		return (1);
	}
	else if (n)
		philo->state->end = 1;
	ft_putnbr(get_time() - philo->state->start);
	write(1, "\t", 1);
	ft_putnbr((philo->p_place + 1));
	write(1, s, ft_strlen(s));
	pthread_mutex_unlock(&philo->state->write);
	return (0);
}

void	f_unlock(t_state *s)
{
	int i;

	i = 0;
	while(i < s->philo->state->n_philo)
	{
		pthread_mutex_unlock(&s->philo[i].eat_m);
		pthread_mutex_unlock(&s->philo[i].temps);
		pthread_mutex_unlock(&s->fork[i++]);
	}
	pthread_mutex_unlock(&s->write);
}

int routine(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	if (eat(philo))
		return (1);
	if (sleep_think(philo))
		return (1);
	return (0);
}

int	start_the_routine(t_state *state)
{
	int i;
	pthread_t *philo_thread;
	philo_thread = malloc(sizeof(pthread_t) * state->n_philo);
	i = 0;
	while (i < state->n_philo - 1)
	{
		pthread_create(&philo_thread[i], NULL, philos_routine, &state->philo[i]);
		i += 2;
	}
	i = 1;
	usleep((state->time_to_eat - 1) * 1000);
	while (i < state->n_philo)
	{
		pthread_create(&philo_thread[i], NULL, philos_routine, &state->philo[i]);
		i += 2;
	}
	if (state->n_philo % 2 == 1)
	{
		usleep((state->time_to_eat - 1) * 1000);
		pthread_create(&philo_thread[(state->n_philo - 1)], NULL, philos_routine, &state->philo[state->n_philo - 1]);
	}
	i = 0;
	while (i < state->n_philo)
		pthread_join(philo_thread[i++], NULL);
	free(philo_thread);
	return (0);
}

void	*philos_routine(void *philo_var)
{
	pthread_t thid;
	t_philo *philo;
	philo = (t_philo *)philo_var;
	pthread_create(&thid, NULL, check_death, philo_var);
	while(1)
	{
		if (routine(philo))
		{
			pthread_join(thid, NULL);
			f_unlock(philo->state);
			return (0);
		}
	}
	pthread_join(thid, NULL);
	f_unlock(philo->state);
	return (0);
}

int get_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

void	clean_thread(t_state *s)
{
	int i;
	f_unlock(s);
	if (s->fork)
	{
		i = 0;
		while (i < s->n_philo)
			pthread_mutex_destroy(&s->fork[i++]);
		free(s->fork);
	}
	if (s->philo)
	{
		i = 0;
		while (i < s->n_philo)
		{
			pthread_mutex_destroy(&s->philo[i].eat_m);
			pthread_mutex_destroy(&s->philo[i++].temps);
		}
		free(s->philo);
	}
	pthread_mutex_destroy(&s->write);
	pthread_mutex_destroy(&s->finish);
}

int main(int argc, char **argv)
{
	t_state state;
	pthread_t tid;
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
		return(error_message("pas le bon nombre d'argument:\n"));
	if(init(&state, argv, argc))
		return(error_message("probleme avec l'initialisation des variables\n"));
	if (argc == 6)
		pthread_create(&tid, NULL, check_last_meal, &state);
	start_the_routine(&state);
	if (argc == 6)
	{
		while (i < state.n_philo)
			pthread_mutex_unlock(&state.philo[i++].eat_m);
		pthread_join(tid, NULL);
	}
	pthread_mutex_lock(&state.finish);
	pthread_mutex_unlock(&state.finish);
	usleep(1000);
	clean_thread(&state);
	return (0);
}
