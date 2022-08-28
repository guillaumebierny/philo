/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:55:16 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/28 23:30:08 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void initialise_philo(t_state *s)
{
	int i;

	i = 0;
	while (i < s->n_philo)
	{
		s->philo[i].p_place = i;
		s->philo[i].is_sleeping = 0;
		s->philo[i].state = s;
		s->philo[i].resting_meal = s->n_of_meal;
		s->philo[i].state = s;
		s->philo[i].pid = 0;
		s->philo[i].resting_time = s->start + s->time_to_die;
		pthread_mutex_init(&s->philo[i].mut_eat, NULL);
		i++;
	}
}

int	check_atoi(int np, int ttd, int tte, int tts)
{
	if (np < 0)
		error_message("number of philo argument is invalid\n");
	if (ttd < 0)
		error_message("time to die argument is invalid\n");
	if (tte < 0)
		error_message("time to eat argument is invalid\n");
	if (tts < 0)
		error_message("time to sleep argument is invalid\n");
	if (np < 0 || ttd < 0 || tte < 0 || tts < 0)
		return (1);
	return (0);
}

int	initialise_v(t_state *s, char **argv, int argc)
{
	int i;

	i = 0;
	s->n_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (check_atoi(s->n_philo, s->time_to_die, s->time_to_eat, s->time_to_sleep))
		return (1);
	if (argc == 6)
		s->n_of_meal = ft_atoi(argv[5]);
	else
		s->n_of_meal = 0;
	if (s->n_of_meal < 0)
		error_message("number of meal argument in invalid\n");
	if (s->n_philo <= 0 || s->time_to_die < 1 || s->n_philo > 200 || s->time_to_die < 60 || s->time_to_eat < 60)
		error_message("mauvais arguments\n");
	if(!(s->philo = malloc(sizeof(t_philo) * s->n_philo)))
		error_message("error: malloc philo\n");
    i = 0;
	sem_unlink("sem_write");
	sem_unlink("sem_fork");
	sem_unlink("sem_died");
	sem_unlink("sem_finish");
	sem_unlink("sem_meal");
    s->sem_write = sem_open("sem_write", O_CREAT | O_EXCL, 0644, 1);
    s->sem_fork = sem_open("sem_fork", O_CREAT | O_EXCL, 0644, s->n_philo);
	s->sem_died = sem_open("sem_died", O_CREAT | O_EXCL, 0644, 1);
	s->sem_finish = sem_open("sem_finish", O_CREAT | O_EXCL, 0644, 1);
	s->sem_meal = sem_open("sem_meal", O_CREAT | O_EXCL, 0644, 1);
	sem_wait(s->sem_meal);
	sem_wait(s->sem_finish);
	s->start = get_time();
    initialise_philo(s);
	return (0);
}