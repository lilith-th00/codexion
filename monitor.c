#include "codexion.h"

int safe_stop(coder_t **coders, int n)
{
    int i;
    int flag;

    while (1)
    {
        i = 0;
        while (i < n)
        {
            pthread_mutex_lock(&coders[i]->data->mutex);
            
            flag = coders[i]->data->flag;
            if(flag == n)
            {
                pthread_mutex_unlock(&coders[i]->data->mutex);
                return (1);
            }
             
            if (get_time() - coders[i]->last_compile >= coders[i]->data->time_to_burnout && (coders[i]->last_compile != 0 || n == 1))
            {
                usleep(50);
                printf("%ld %d burned out\n", time_task(coders[i]->data->time), coders[i]->id);
                pthread_mutex_unlock(&coders[i]->data->mutex);
                return (1);
            }
            pthread_mutex_unlock(&coders[i]->data->mutex);
            i++;
        }
    }
}

void *monitor(void *args)
{
    int num_coders;

    coder_t **coders = (coder_t **)args;
    pthread_mutex_lock(&coders[0]->data->mutex);
    num_coders = coders[0]->data->number_of_coders;
    pthread_mutex_unlock(&coders[0]->data->mutex);
    if (safe_stop(coders, num_coders) == 1)
        return (NULL);
    return (NULL);
}

