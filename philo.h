#include <time.h>
#include <pthread.h>

typedef struct philo
{
    int n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_die;
    int is_eating;
    int is_sleeping;
    int is_thinking;
    pthread_mutex_t write;
    pthread_mutex_t fork

}