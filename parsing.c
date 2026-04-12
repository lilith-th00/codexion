#include "codexion.h"

int has_digit(char *s)
{
    int i;

    i = 0;
    while (s[i] && (s[i] != '-'))
    {
        if (s[i] >= '0' && s[i] <= '9')
            return (1);
        i++;
    }
    return (0);
}
int valid_scheduler(char *str)
{
    if (strcmp(str, "fifo") != 0 && strcmp(str, "edf") != 0)
        return (0);
    return (1);
}

//min or max of int

int ft_pars_args(int ac, char **av)
{
    int i;
    if (ac != 9)
        return (0);
    i = 1;
    while (i < ac - 1)
    {
        if (!has_digit(av[i]))
            return (0);
        i++;
    }
    if (!valid_scheduler(av[8]))
        return (0);
}
void ft_strcpy(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
void store_values(char **av, data_t *data)
{
    data->number_of_coders = atoi(av[1]);
    data->time_to_burnout = atoi(av[2]);
    data->time_to_compile = atoi(av[3]);
    data->time_to_debug = atoi(av[4]);
    data->time_to_refactor = atoi(av[5]);
    data->number_of_compiles_required = atoi(av[6]);
    data->dongle_cooldown = atoi(av[7]);
    ft_strcpy(data->scheduler, av[8]);

}