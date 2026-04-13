#include "codexion.h"

int create_coders(coder_t *coders, int n)
{
    //free
    coders = malloc(sizeof(coder_t) * n);
    if (!coders)
        return (0);
    return (1);
}
int create_dongles(dongle_t *dongles, int n)
{
    //free
    dongles = malloc(sizeof(coder_t) * n);
    if (!dongles)
        return (0);
    return (1);
}




