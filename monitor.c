#include "codexion.h"

void *monitor(void *args)
{
    int n;
    int i;
    int time_bur;
    coder_t **coders = (coder_t **)args;

    n = coders[0]->data->number_of_coders;
    time_bur = coders[0]->data->time_to_burnout;
    while (1)
    {
        i = 0;
        while (i < n)
        {
            if ((get_time() - coders[i]->time_burnout) >= time_bur && coders[i]->time_burnout != 0)
            {
                printf("coder %d now %ld last compile %ld\n", coders[i]->id, get_time() ,coders[i]->time_burnout);
                usleep(10 * 1000);
                printf("%ld %d burned out\n", time_task(coders[i]->data->time), coders[i]->id);
                exit(1);
            }
            else if (coders[i]->data->n_compiles == coders[i]->data->number_of_compiles_required * n)
                exit(1);
            i++;
        }
    }
    return (NULL);
}
