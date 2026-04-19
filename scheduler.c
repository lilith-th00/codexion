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
        //printf("%d\n", node->coder->id);
        node = node->next;
    }
}
node_t *insert_tail(node_t *head, coder_t *coder)
{
    node_t *tmp = head;

    // 🔍 check if already exists + find last node
    while (tmp)
    {
        if (tmp->coder->id == coder->id)
            return head; // already in list

        if (!tmp->next)
            break;
        tmp = tmp->next;
    }

    node_t *new = create_node(coder);
    if (!new)
        return head;

    if (!head)
        return new;

    tmp->next = new;
    print_list(head);

    return head;
}
node_t *delete_value(node_t *head, coder_t *coder)
{
    node_t *tmp = head;
    node_t *prev = NULL;

    while (tmp)
    {
        if (tmp->coder->id == coder->id)
        {
            if (prev)
                prev->next = tmp->next;
            else
                head = tmp->next;

            //free(tmp);
            return head;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return head;
}
int fifo(coder_t *coder, node_t *head)
{
    if (!head)
        return (0);
    if (head->coder->id == coder->id)
        return (1);
    return (0);
}
