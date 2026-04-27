/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:22:57 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/23 14:43:41 by ikabboud         ###   ########.fr       */
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

node_t *create(node_t *head, coder_t *coder)
{
    if (strcmp(coder->data->scheduler, "fifo") == 0)
        return (insert_tail(head, coder));
    else
        return (insert_sorted(head, coder));
}
void take_dongle(dongle_t *d, coder_t *coder)
{
    long ms;
    long time;
    
    pthread_mutex_lock(&d->dongle_mutex);
    d->head = create(d->head, coder);
    while (!fifo_edf(coder, d->head))
        pthread_cond_wait(&d->cond, &d->dongle_mutex);
    time = get_time();
    pthread_mutex_lock(&coder->data->mutex);
    ms = time - d->cooldown_time;

    if (ms < coder->data->dongle_cooldown)
        usleep((coder->data->dongle_cooldown - ms) * 1000);
    printf("%ld %d has taken a dongle\n", time_task(coder->data->time), coder->id);
    pthread_mutex_unlock(&coder->data->mutex);
    
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
void do_compile(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is compiling\n", time_task(coder->data->time), coder->id);
    printf("finn wsalt %d, coder %d \n", coder->n_compiles, coder->id);
    usleep(coder->data->time_to_compile * 1000);
    pthread_mutex_unlock(&coder->data->mutex);
}
void *task(void *args)
{
    coder_t *coder;
    dongle_t *first;
    dongle_t *second;
    
    coder = (coder_t *)args;
    while (1)
    {
        pthread_mutex_lock(&coder->data->mutex);
        if (coder->n_compiles >= coder->data->number_of_compiles_required)
        {
            coder->data->flag += 1;
            pthread_mutex_unlock(&coder->data->mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&coder->data->mutex);
        if (coder->id % 2 != 0)
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
        
        pthread_mutex_lock(&coder->data->mutex);
        coder->n_compiles += 1;
        coder->last_compile = get_time();
        pthread_mutex_unlock(&coder->data->mutex);
        first->cooldown_time = get_time();
        first->head = delete_value(first->head, coder);
        pthread_cond_broadcast(&first->cond);
        pthread_mutex_unlock(&first->dongle_mutex);
        second->cooldown_time = get_time();
        second->head = delete_value(second->head, coder);
        pthread_cond_broadcast(&second->cond);
        pthread_mutex_unlock(&second->dongle_mutex);
    
        do_debug(coder);
        do_refactor(coder);
    }
}



#include "codexion.h"

long time_task(long time)
{
    struct timeval t2;
    long ms;

    gettimeofday(&t2, NULL);
    ms = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
    return (ms - time);
}

node_t *create(node_t *head, coder_t *coder)
{
    if (strcmp(coder->data->scheduler, "fifo") == 0)
        return (insert_tail(head, coder));
    else
        return (insert_sorted(head, coder));
}


void take_dongle(dongle_t *d, coder_t *coder)
{
    long ms;
    long now;

    pthread_mutex_lock(&d->dongle_mutex);

    d->head = create(d->head, coder);

    while (!fifo_edf(coder, d->head))
        pthread_cond_wait(&d->cond, &d->dongle_mutex);

    now = get_time();

    ms = now - d->cooldown_time;
    if (ms < coder->data->dongle_cooldown)
    {
        pthread_mutex_unlock(&d->dongle_mutex);
        usleep((coder->data->dongle_cooldown - ms) * 1000);
        pthread_mutex_lock(&d->dongle_mutex);
    }

    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d has taken a dongle\n",
        time_task(coder->data->time), coder->id);
    pthread_mutex_unlock(&coder->data->mutex);
}


void do_compile(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is compiling\n",
        time_task(coder->data->time), coder->id);
    pthread_mutex_unlock(&coder->data->mutex);

    usleep(coder->data->time_to_compile * 1000);
}

void do_debug(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is debugging\n",
        time_task(coder->data->time), coder->id);
    pthread_mutex_unlock(&coder->data->mutex);

    usleep(coder->data->time_to_debug * 1000);
}

void do_refactor(coder_t *coder)
{
    pthread_mutex_lock(&coder->data->mutex);
    printf("%ld %d is refactoring\n",
        time_task(coder->data->time), coder->id);
    pthread_mutex_unlock(&coder->data->mutex);

    usleep(coder->data->time_to_refactor * 1000);
}


void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!data->stop)
    {
        i = 0;
        while (i < data->number_of_coders)
        {
            if (get_time() - data->coders[i].last_compile
                > data->time_to_burnout)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d burned out\n",
                    get_time() - data->start_time,
                    data->coders[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                data->stop = 1;
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}


void *task(void *args)
{
    coder_t *coder = (coder_t *)args;
    dongle_t *first;
    dongle_t *second;

    while (1)
    {
        pthread_mutex_lock(&coder->data->mutex);
        if (coder->n_compiles >= coder->data->number_of_compiles_required)
        {
            coder->data->flag += 1;
            pthread_mutex_unlock(&coder->data->mutex);
            return NULL;
        }
        pthread_mutex_unlock(&coder->data->mutex);

        if (coder->id % 2 == 0)
        {
            first = coder->right_d;
            second = coder->left_d;
        }
        else
        {
            first = coder->left_d;
            second = coder->right_d;
        }

        take_dongle(first, coder);
        take_dongle(second, coder);

        do_compile(coder);

        pthread_mutex_lock(&coder->data->mutex);
        coder->n_compiles += 1;
        coder->last_compile = get_time();
        pthread_mutex_unlock(&coder->data->mutex);

        pthread_mutex_lock(&first->dongle_mutex);
        first->cooldown_time = get_time();
        first->head = delete_value(first->head, coder);
        pthread_cond_broadcast(&first->cond);
        pthread_mutex_unlock(&first->dongle_mutex);

        pthread_mutex_lock(&second->dongle_mutex);
        second->cooldown_time = get_time();
        second->head = delete_value(second->head, coder);
        pthread_cond_broadcast(&second->cond);
        pthread_mutex_unlock(&second->dongle_mutex);

        do_debug(coder);
        do_refactor(coder);
    }
}

//safe check : check is stop wach 
/*
    int check_stop()
    {
        int i;
        lock
        i = stop;  //wahed variable f data | monitor!
        unlock
        reutrn i;
    }

    itn safe_stop() //monitor burn and all_compile
    {
        lock
        stop =  1;
        unlock
    }
*/
