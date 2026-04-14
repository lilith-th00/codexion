#include "codexion.h"

int create_coders(coder_t ***coders, int n)
{
    int i;
    //free
    *coders = malloc(sizeof(coder_t *) * n);
    if (!coders)
        return (0);
    i = 0;
    while (i < n)
    {
        (*coders)[i] = malloc(sizeof(coder_t));
        if (!(*coders)[i])
            return (0);
        i++;
    }
    return (1);
}
int create_dongles(dongle_t ***dongles, int n)
{
    int i;
    //free
    *dongles = malloc(sizeof(dongle_t *) * n);
    if (!*dongles)
        return (0);
    i = 0;
    while (i < n)
    {
        //free
        (*dongles)[i] = malloc(sizeof(dongle_t));
        if (!(*dongles)[i])
            return (0);
        i++;
    }

    return (1);
}
void mutex_cond_init(dongle_t **dongles, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        pthread_mutex_init(&(dongles[i]->dongle), NULL);
        i++;
    }
}




