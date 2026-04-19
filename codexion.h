#ifndef CODEXION_H
#define CODEXION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef struct coder_s coder_t;
typedef struct dongle_s dongle_t;
typedef struct data_s
{
    //data
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
    int order;
    int n_compiles;
    long time;
    pthread_t minitor_t; //get_time() reference dyal ga3 coders
} data_t;

typedef struct node_s
{
    coder_t *coder;
    struct node_s *next;
} node_t;


typedef struct dongle_s //shared memory mabin coderSS | monitr
{
    int id; //
    long cooldown_time; // = get_time() assign fach an7ato dongles! | mutex
    pthread_mutex_t dongle_mutex;
    pthread_cond_t cond;   //ay haja f dongle andiro lihe dongle_mutex
    node_t *head;
    node_t *tail;
} dongle_t;

typedef struct coder_s
{
    int id;
    pthread_t   thread_id;
    dongle_t *left_d;
    dongle_t *right_d;
    data_t *data;
    long time_burnout;
} coder_t;

int valid_not(int ac, char **av);
void store_values(data_t *data, char **av);
coder_t **create_coders(data_t *data, dongle_t **dongles); 
dongle_t **create_dongles(int n);
void helper(coder_t **coders);
void create_thread(coder_t **coders, int n, void *task);
void join_thread(coder_t **coders, int n);
void *task(void *args);
char *ft_strdup(char *s);
long get_time();
long time_task(long time);
void *monitor(void *args);
node_t *insert_tail(node_t *head, coder_t *coder);
node_t *delete_value(node_t *head, coder_t *coder);
int fifo(coder_t *coder, node_t *head);






#endif 
