#include "codexion.h"

void create_thread_join(coder_t *coders, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        coders[i].id = i + 1;
        pthread_create(&coders[i].thread_id, NULL, task, NULL);
        i++;
    }
    i = 0;
    while (i < n)
    {
        pthread_join(coders[i].thread_id, NULL);
        i++;
    }
}
