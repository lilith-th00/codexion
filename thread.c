/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:23:07 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/23 10:31:22 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void create_thread(coder_t **coders, int n, void *task, data_t *data, void *monitor)//khas n9ad pointer to funt
{
    int i;
    
    i = 0;
    while (i < n)
    {
        pthread_mutex_lock(&coders[i]->data->mutex);
        coders[i]->data->time = get_time();
        pthread_mutex_unlock(&coders[i]->data->mutex);
        if (pthread_create(&coders[i]->thread_id, NULL, task, coders[i]) != 0)
        {
            printf("ERROR");
            exit(1);
        }
        i++;
    }
    if (pthread_create(&data->minitor_t, NULL, monitor, coders) != 0)
    {
        printf("ERROR");
        exit(1);
    }
}
void join_thread(coder_t **coders, int n, data_t *data)
{
    int i;

    i = 0;
    while (i < n)
        pthread_join(coders[i++]->thread_id, NULL);
    pthread_join(data->minitor_t, NULL);
}

