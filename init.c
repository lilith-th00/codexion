#include "codexion.h"

void free_coders(coder_t **coders, int n)
{
    int i;

    i = 0;
    while (i <= n)
        free(coders[i++]);
    free(coders);
}
void free_dongles(dongle_t **dongles, int n)
{
    int i;

    i = 0;
    while (i <= n)
        free(dongles[i++]);
    free(dongles);
}

coder_t **create_coders(data_t *data, dongle_t **dongles)
{
    coder_t **coders;
    int i;
    int n;
    
    n = data->number_of_coders;
    //free
    coders = malloc(sizeof(coder_t*) * n);
    if (!coders)
        return (NULL);
    i = 0;
    while (i < n)
    {
        coders[i] = malloc(sizeof(coder_t));
        if (!coders[i])
        {
            free_coders(coders, i);
            return (NULL);
        }
        coders[i]->id = i + 1;
        coders[i]->left_d = dongles[(i + n - 1) % n];
        coders[i]->right_d = dongles[i];
        coders[i++]->data = data;
    }
    return (coders);
}
dongle_t **create_dongles(int n)
{
    dongle_t **dongles;
    int i;
    
    dongles = malloc(sizeof(dongle_t*) * n);
    if (!dongles)
        return (NULL);
    i = 0;
    while (i < n)
    {
        dongles[i] = malloc(sizeof(dongle_t));
        if (!dongles[i])
        {
            free_dongles(dongles, i);
            return (NULL);
        }

        dongles[i]->id = i;
        i++;
    }

    return (dongles);
}
