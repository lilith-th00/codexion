#include "codexion.h"

void create_thread_join(coder_t **coders, int n, void *(*f)(void*))
{
    int i;

    i = 0;
    while (i < n)
    {
        struct timeval t;
        gettimeofday(&t, NULL);
        coders[i]->id = i + 1;
        coders[i]->data->time = t;
        pthread_create(&coders[i]->thread_id, NULL, f, coders[i]);
        i++;
    }
    i = 0;
    while (i < n)
    {
        pthread_join(coders[i]->thread_id, NULL);
        i++;
    }
}
