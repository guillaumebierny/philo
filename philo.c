#include "philo.h"

void take_fork()
{
	pthread_mutex_lock(&left_fork)
	message();
	pthread_mutex_lock(rihgt_fork)
	message();
}


display_message()
{
	pthread_mutex_lock(&write);
	message(philo, time, action);
	pthread_mutex_unlock(&write);
}

void eat()
{
	display_message();
	usleep(philo->time_to_eat)
	before_to_die = get_time() + philo->time_to_die
}

void sleep_and_think()
{
	pthread_mutex_unlock(&lfork);
	pthread_mutex_unlock(&rfork);
	message();
	usleep(time_to_sleep);
	message();

}

void *philos_routine()
{
	check_if_dying()
	while(1)
	{
		take_fork();
		eat();
		sleep();
	}
}

void	init(pthread_t *philo, char **argv)
{
	int n_philo = ft_atoi(argv[1]);

	philo = malloc(sizeof() * n_philo)
	
}

int main(int argc, char **argv)
{
	pthread_t *philo;
	init(philo, argv);
	while ()
	{
		pthread_create()
	}
	return (0);



}