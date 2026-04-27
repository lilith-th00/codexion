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


#include "codexion.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!data->stop)
    {
        i = 0;
        while (i < data->number_of_coders)
        {
            if (get_time() - data->coders[i].last_compile
                > data->time_to_burnout)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d burned out\n",
                    get_time() - data->start_time,
                    data->coders[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                data->stop = 1;
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}


//

#include "codexion.h"

node_t *create_node(coder_t *coder)
{
    node_t *node;

    node = malloc(sizeof(node_t));
    if (!node)
        return (NULL);
    node->coder = coder;
    node->next = NULL;
    return (node);
}

void print_list(node_t *head)
{
    while (head)
    {
        printf("%d\n", head->coder->id);
        head = head->next;
    }
}

node_t *insert_tail(node_t *head, coder_t *coder)
{
    node_t *new = create_node(coder);
    node_t *tmp;

    if (!new)
        return (head);

    if (!head)
        return (new);

    tmp = head;
    while (tmp->next)
    {
        if (tmp->coder && tmp->coder->id == coder->id)
            return (head);
        tmp = tmp->next;
    }
    if (tmp->coder && tmp->coder->id == coder->id)
        return (head);

    tmp->next = new;
    return (head);
}

node_t *delete_value(node_t *head, coder_t *coder)
{
    node_t *tmp = head;
    node_t *prev = NULL;

    while (tmp)
    {
        if (tmp->coder->id == coder->id)
        {
            if (!prev)
                head = tmp->next;
            else
                prev->next = tmp->next;

            free(tmp);
            return (head);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (head);
}

int fifo_edf(coder_t *coder, node_t *head)
{
    if (!head || !head->coder)
        return (0);
    return (head->coder->id == coder->id);
}

node_t *insert_sorted(node_t *head, coder_t *coder)
{
    node_t *node = create_node(coder);
    node_t *tmp = head;
    node_t *prev = NULL;

    if (!node)
        return (head);

    // duplicate check
    while (tmp)
    {
        if (tmp->coder->id == coder->id)
            return (head);
        tmp = tmp->next;
    }

    // insertion f début
    if (!head || coder->last_compile < head->coder->last_compile)
    {
        node->next = head;
        return (node);
    }

    tmp = head;
    while (tmp && tmp->coder->last_compile < coder->last_compile)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    prev->next = node;
    node->next = tmp;

    return (head);
}

