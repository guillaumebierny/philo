#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// int get_time()
// {
//     struct timeval t;
//     gettimeofday(&t, NULL);
//     return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
// }

typedef struct s
{
    int x;
}   t;

void *test(void *v_v)
{
    t *v;
    v = (t *)v_v;
    sleep(2);
    v->x = 0;
    sleep(2);
    printf("fin du thread\n");
    pthread_exit(NULL);
}

int main()
{
    t v;
    v.x = 1;
    pthread_t thread;
    pthread_create(&thread, NULL, test, &v);
    pthread_detach(thread);
    while (v.x)
        usleep(100);
    printf("terminer\n");
}
