#include "codexion.h"

void helper(coder_t **coders, dongle_t **dongles)
{

}


int main(int ac, char **av)
{
    data_t *data;
    coder_t **coders;   
    dongle_t **dongles;

    if (ac != 9)
        return (0);
    if (!valid_not(ac, av))
        return (0);
    data = malloc(sizeof(data_t));
    if (!data)
        return (0);
    store_values(data, av);
    if (!data->scheduler)
    {
        free(data);
        return (0);
    }
    dongles = create_dongles(data->number_of_coders);
    coders = create_coders(data, dongles);
    //helper(coders, dongles);
    printf("nadiiiiiiia\n");
}
