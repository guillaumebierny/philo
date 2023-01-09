/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:55:14 by gbierny           #+#    #+#             */
/*   Updated: 2023/01/09 16:11:26 by gbierny          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < s->philo->state->n_philo)
	{
		pthread_mutex_unlock(&s->philo[i].eat_m);
		pthread_mutex_unlock(&s->philo[i].temps);
		pthread_mutex_unlock(&s->fork[i++]);
	}
	pthread_mutex_unlock(&s->write);
}

int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

void	clean_thread(t_state *s)
{
	int	i;

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

int	main(int argc, char **argv)
{
	t_state		state;
	pthread_t	tid;
	int			i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (err_msg("put: exec t_death t_eat t_sleep (n_meal)\n"));
	if (init(&state, argv, argc))
		return (err_msg("initialisation of variable issue\n"));
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
