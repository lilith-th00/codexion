/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:23:39 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/23 10:23:15 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int valid_num(int n)
{
    if (n <= 0 || n < INT_MIN || n > INT_MAX)
        return (0);
    return (1);
}

int valid_not(int ac, char **av)
{
    int i;

    i = 1;
    while (i < ac -1)
    {
        if (!valid_num(atoi(av[i])))
            return (0);
        i++;
    }
    if (strcmp(av[ac-1], "fifo") != 0  && strcmp(av[ac-1], "edf") != 0)
        return (0);
    return (1);
}

void store_values(data_t *data, char **av)
{
    data->number_of_coders = atoi(av[1]);
    data->time_to_burnout = atoi(av[2]);
    data->time_to_compile = atoi(av[3]);
    data->time_to_debug = atoi(av[4]);
    data->time_to_debug = atoi(av[5]);
    data->number_of_compiles_required = atoi(av[6]);
    data->dongle_cooldown = atoi(av[7]);
    data->scheduler = ft_strdup(av[8]);
    data->flag = 0;
    pthread_mutex_init(&data->mutex, NULL);
}
