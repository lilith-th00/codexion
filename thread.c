#include "codexion.h"

void create_thread(coder_t **coders, int n, void *(*f)(void*))
{
    int i;

    i = 0;
    while (i < n)
    {
        coders[i]->data->time = get_time();
        pthread_create(&coders[i]->thread_id, NULL, f, coders[i]);
        i++;
    }
}
void join_thread(coder_t **coders, int n)
{
    int i;

    i = 0;
    while (i < n)
        join_thread(coders[i++], NULL);
}

