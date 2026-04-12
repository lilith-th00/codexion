#include "codexion.h"

int main(int ac, char **av)
{
    data_t *data;

    if (ft_pars_args(ac, av) == 0)
        return (0);
    //free
    data = malloc(sizeof(data_t));
    if (!data)
        return (0);
    //free
    data->scheduler = malloc((strlen(av[8]) + 1) * sizeof(char));
    if (!data->scheduler)
        return (0);
    store_values(av, data);


    printf("%d\n", data->number_of_coders);
    printf("%d\n", data->time_to_burnout);
    printf("%d\n", data->time_to_compile);
    printf("%d\n", data->time_to_debug);
    printf("%d\n", data->time_to_refactor);
    printf("%d\n", data->number_of_compiles_required);
    printf("%d\n", data->dongle_cooldown);
    printf("%s\n", data->scheduler);
}

