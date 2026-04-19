/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:23:07 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/19 16:43:38 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void create_thread(coder_t **coders, int n, void *task)
{
    int i;


    i = 0;
    while (i < n)
    {
        pthread_mutex_lock(&coders[i]->data->mutex);
        coders[i]->data->time = get_time();
        pthread_mutex_unlock(&coders[i]->data->mutex);
        pthread_create(&coders[i]->thread_id, NULL, task, coders[i]);
        i++;
    }
    //pthread_create(&data->minitor_t, NULL, monitor, coders);
    
}
void join_thread(coder_t **coders, int n)
{
    int i;

    i = 0;
    while (i < n)
        pthread_join(coders[i++]->thread_id, NULL);
    //pthread_join(data->minitor_t, NULL);
}

