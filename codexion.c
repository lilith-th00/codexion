#include "codexion.h"


void odd_even(dongle_t **dongles, coder_t *coder, int n, int id)
{
    int left;
    int right;

    left = id - 2;
    right = id - 1;

    if (id == 1)
        left = n - 1;

    
    if (id % 2 == 0)
    {
        coder->right_d = dongles[right];
        coder->left_d = dongles[left];
    }
    else
    {
        coder->left_d = dongles[left];
        coder->right_d = dongles[right];
    }
}


void data_dongle(data_t *data, coder_t **coders, dongle_t **dongles)
{
    int i;
    int n;

    i = 0;
    n = data->number_of_coders;
    while (i < n)
    {
        coders[i]->data = data;
        odd_even(dongles, coders[i], n, i+1);
        i++;   
    }
}

void helper(data_t *data, coder_t **coders, dongle_t **dongles)
{
    mutex_cond_init(dongles, data->number_of_coders);
    data_dongle(data, coders, dongles);
    sim_coders(coders, data->number_of_coders);

}

int main(int ac, char **av)
{
    data_t *data;
    coder_t **coders;
    dongle_t **dongles;

    if (ft_pars_args(ac, av) == 0)
        return (0);
    // free
    data = malloc(sizeof(data_t));
    if (!data)
        return (0);
    // free

    data->scheduler = malloc((strlen(av[8]) + 1) * sizeof(char));
    if (!data->scheduler)
        return (0);
    
    store_values(av, data);

    create_coders(&coders, data->number_of_coders);
    create_dongles(&dongles, data->number_of_coders);
    helper(data, coders, dongles);
}
