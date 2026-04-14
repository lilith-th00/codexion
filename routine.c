#include "codexion.h"

long time_task(struct timeval t1)
{
    struct timeval t2;
    long ms1;
    long ms2;

    gettimeofday(&t2, NULL);
    ms1 = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
    ms2 = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
    return (ms2 - ms1);
}

void take_dongle(dongle_t *d, int t_cooldown)
{
    long ms1;
    long ms2;
    long ms;
    struct timeval time;

    gettimeofday(&time, NULL);
    ms1 = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    ms2 = (d->last_time.tv_sec * 1000) + (d->last_time.tv_usec / 1000);
    ms = ms1 - ms2;
    if (ms < t_cooldown)
        usleep((t_cooldown - ms) * 1000);
    pthread_mutex_lock(&d->dongle);
    gettimeofday(&d->last_time, NULL);
}
void left_right(coder_t *coder, int n)
{
    if (n % 2 == 0)
    {
        take_dongle(coder->right_d, coder->data->time_to_burnout);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
        take_dongle(coder->left_d, coder->data->time_to_burnout);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
    }
    else
    {
        take_dongle(coder->left_d, coder->data->dongle_cooldown);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
        take_dongle(coder->right_d, coder->data->dongle_cooldown);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
    }
}
void *task(void *args)
{
    coder_t *coder = (coder_t *)args;

    left_right(coder, coder->id);
    printf("%ld %d is compiling\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_compile * 1000);
    pthread_mutex_unlock(&coder->left_d->dongle);
    gettimeofday(&coder->left_d->last_time, NULL);
    pthread_mutex_unlock(&coder->right_d->dongle);
    gettimeofday(&coder->right_d->last_time, NULL);
}
void sim_coders(coder_t **coders, int n)
{
    create_thread_join(coders, n, task);
}
