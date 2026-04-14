#ifndef CODEXION_H
#define CODEXION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

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
    struct timeval time;
}data_t;

typedef struct dongle_s
{
    int id;
    //(size, capacity)
    struct timeval last_time;
    pthread_mutex_t dongle;
}dongle_t;

typedef struct coder_s
{
    int     id;
    pthread_t   thread_id;
    dongle_t *left_d;
    dongle_t *right_d;
    data_t *data;
} coder_t;

int ft_pars_args(int ac, char **av);
void store_values(char **av, data_t *data);
int create_coders(coder_t ***coders, int n);
int create_dongles(dongle_t ***dongles, int n);
void create_thread_join(coder_t **coders, int n, void *(*f)(void*));
void mutex_cond_init(dongle_t **dongles, int n);
void sim_coders(coder_t **coders, int n);
void *task(void *args);








#endif 