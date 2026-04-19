/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikabboud <ikabboud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:23:18 by ikabboud          #+#    #+#             */
/*   Updated: 2026/04/16 18:23:20 by ikabboud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//safe_stop: monitor: safely reading/writing stop flag!

char *ft_strdup(char *s)
{
    char *str;
    int i;

    str = malloc(sizeof(char) * (strlen(s) + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}
long get_time()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}


/*

void    safe_print()
{
    //lock
    printf("log: compilig, debuging, refactor");
    //unlcok
}
*/

