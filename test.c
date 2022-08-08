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
    int i = 0;
    int x = 3;
    while (x--)
        i += 5;
    printf("i = %d\n", i);
    return (0);
}

int main()
{
    t v;
    v.x = 1;
    int i;
    i = 0;
    pthread_t thread;
    int x = 3;
    while (x--)
        pthread_create(&thread, NULL, test, &v);
    x = 3;
    while (x--)
        pthread_join(thread, NULL);
}
