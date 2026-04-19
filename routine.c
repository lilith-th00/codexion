/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:22:57 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/19 17:30:42 by ikabboud         ###   ########.fr       */
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
    pthread_mutex_lock(&d->dongle_mutex);

    d->head = insert_tail(d->head, coder);

    while (!fifo(coder, d->head))
    {
        
        pthread_cond_wait(&d->cond, &d->dongle_mutex);
    }
    long time = get_time();
    long ms = time - d->cooldown_time;

    if (ms < coder->data->dongle_cooldown)
    {
        usleep((coder->data->dongle_cooldown - ms) * 1000);
    }
    //pthread_mutex_unlock(&d->dongle_mutex);
}
void do_debug(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is debugging\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_debug * 1000);
    pthread_mutex_unlock(&coder->data->mutex);
}
void do_refactor(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is refactoring\n", time_task(coder->data->time), coder->id);
    usleep(coder->data->time_to_refactor * 1000);
    pthread_mutex_unlock(&coder->data->mutex);
}

void task(coder_t *coder)
{
    dongle_t *first;
    dongle_t *second;

    if (coder->left_d < coder->right_d)
    {
        first = coder->left_d;
        second = coder->right_d;
    }
    else
    {
        first = coder->right_d;
        second = coder->left_d;
    }

    take_dongle(first, coder);   
    take_dongle(second, coder);  

    do_compile(coder);

    first->cooldown_time = get_time();
    first->head = delete_value(first->head, coder->id);
    pthread_cond_broadcast(&first->cond);
    pthread_mutex_unlock(&first->dongle_mutex);

    second->cooldown_time = get_time();
    second->head = delete_value(second->head, coder->id);
    pthread_cond_broadcast(&second->cond);
    pthread_mutex_unlock(&second->dongle_mutex);
}
