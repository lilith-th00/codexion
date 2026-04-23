/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:22:37 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/23 10:26:43 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void helper(coder_t **coders, data_t *data)
{
    int n;

    n = coders[0]->data->number_of_coders;
    create_thread(coders, n, task, data, monitor);
    join_thread(coders, n, data);
}
int main(int ac, char **av)
{
    data_t *data;
    coder_t **coders; 
    dongle_t **dongles;

    if (ac != 9)
        return (0);
    if (!valid_not(ac, av))
        return (0);
    data = malloc(sizeof(data_t));
    if (!data)
        return (0);
    store_values(data, av);
    if (!data->scheduler)
    {
        free(data);
        return (0);
    }
    dongles = create_dongles(data->number_of_coders);
    coders = create_coders(data, dongles);
    helper(coders, data);
    return (0);
}
