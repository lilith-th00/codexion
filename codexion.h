#ifndef CODEXION_H
#define CODEXION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct data_s
{
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
}data_t;

typedef struct dongle_s
{
    int id;
    //(size, capacity)
    //last_used
    //mutex_dongle
}dongle_t;

typedef struct s_coder
{
    int     id;
    pthread_t   thread_id;
    dongle_t *left_d;
    dongle_t *right_d;
    //
} t_coder;

int ft_pars_args(int ac, char **av);
void store_values(char **av, data_t *data);









#endif 