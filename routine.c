/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:22:57 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/19 02:58:28 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long time_task(long time)
{
    struct timeval t2;
    long ms;

    gettimeofday(&t2, NULL);
    ms = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
    return (ms - time);
}
void take_dongle(dongle_t *d, coder_t *coder)
{
    printf("%d\n", coder->id);

    pthread_mutex_lock(&d->dongle_mutex);

    d->head = insert_tail(d->head, coder);

    while (1)
    {
        long time = get_time();
        long ms = time - d->cooldown_time;

        if (ms >= coder->data->dongle_cooldown &&
            fifo(coder, d->head))
        {
            return; // mutex stays locked (by design)
        }

        pthread_cond_wait(&d->cond, &d->dongle_mutex);
    }
}

void do_debug(coder_t *coder)
{
    printf("%ld %d is debugging\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_debug * 1000);
}
void do_refactor(coder_t *coder)
{
    printf("%ld %d is refactoring\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_refactor * 1000);
}
void left_right(coder_t *coder, int n)
{
    if (n % 2 == 0)
    {
        take_dongle(coder->right_d, coder);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
        take_dongle(coder->left_d, coder);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
    }
    else
    {
        take_dongle(coder->left_d, coder);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
        take_dongle(coder->right_d, coder);
        printf("%ld %d has taken a dongle\n", time_task(coder->data->time), n);
    }
}
void *task(void *args)
{
    coder_t *coder = (coder_t *)args;

    left_right(coder, coder->id);
    printf("%ld %d is compiling\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_compile * 1000);
    coder->time_burnout = get_time();
    
    coder->left_d->cooldown_time = get_time();
    coder->left_d->head = delete_value(coder->left_d->head, coder);

    coder->right_d->cooldown_time = get_time();
    coder->right_d->head = delete_value(coder->right_d->head, coder);

    pthread_cond_broadcast(&coder->left_d->cond);
    pthread_cond_broadcast(&coder->right_d->cond);

    pthread_mutex_unlock(&coder->left_d->dongle_mutex);
    pthread_mutex_unlock(&coder->right_d->dongle_mutex);

    do_debug(coder);
    do_refactor(coder);

    return NULL;
}
