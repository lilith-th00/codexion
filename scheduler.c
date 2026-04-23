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
    node_t *node;

    node = head;
    while (node)
    {
        printf("%d\n", node->coder->id);
        node = node->next;
    }
}
node_t *insert_tail(node_t *head, coder_t *coder)
{
    node_t *new = create_node(coder);
    if (!new)
        return head;

    if (!head)
        return new;

    node_t *tmp = head;

    while (tmp->next)
    {
        if (tmp->coder && tmp->coder->id == coder->id)
            return head;
        tmp = tmp->next;
    }
    if (tmp->coder && tmp->coder->id == coder->id)
        return head;

    tmp->next = new;
    print_list(head);
    return head;
}
node_t *delete_value(node_t *head, coder_t *coder)
{
    node_t *tmp;

    if (!head)
        return (NULL);

    if(head->coder->id == coder->id)
    {
        tmp = head->next;
        free(head);
        return (tmp);
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
    node_t *tmp;                                                                                    
    node_t *node;
    node_t *ex_node;

    if (head)
    {
        tmp = head;
        while (tmp->next)
        { 
            if (tmp->coder->id == coder->id)
                return (head);
            tmp = tmp->next;
        }
    }
    node = create_node(coder);
    if (!head)
        return (node);
    tmp = head;
    while (tmp->next && tmp->coder->last_compile < coder->last_compile)
    {
        ex_node = tmp;
        tmp = tmp->next;
    }
    if (tmp->next)
    {
        ex_node->next = node;
        node->next = tmp;
    }
    print_list(head);
    return (head);
}