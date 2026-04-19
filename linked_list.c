#include <stdlib.h>
#include <stdio.h>

typedef struct node_s
{
    int n;
    struct node_s *next;
} node_t;


node_t *create_node(int n)
{
    node_t *node;

    node = malloc(sizeof(node_t));
    if (!node)
        return (NULL);
    node->n = n;
    node->next = NULL;
    return (node);
}
void print_list(node_t *head)
{
    node_t *node;

    node = head;
    while (node)
    {
        printf("%d\n", node->n);
        node = node->next;
    }
}
node_t *insert_tail(node_t *head, int value)
{
    node_t *node;
    node_t *nodee;

    node = create_node(value);
    if (!node)
        return head;
    if (!head)
    return node;

    nodee = head;
    while (nodee->next)
        nodee = nodee->next;
    nodee->next = node;
    node->next = NULL;
    return (head);
}
int len_of_nodes(node_t *head)
{
    int i;

    i = 0;
    while (head)
    {
        head = head->next;
        i++;
    }
    return (i);
}


node_t *insert_sorted(node_t *head, int value)
{
    node_t *new_node;
    node_t *tmp;

    new_node = create_node(value);

    if (!new_node)
        return (head);
    if (!head)
        return (new_node);
    tmp = head;
    while (tmp->next && tmp->next->n < value)
        tmp = tmp->next;
    new_node = tmp;
    tmp->next = new_node; 
    return (head);
}

node_t *delete_value(node_t *head, int value)
{
    node_t *tmp;
    node_t *node;
    node_t *next_node;

    tmp = head;
    if (!head)
        return NULL;
    if (tmp->n == value)
    {
        node = tmp->next;
        free(tmp);
        return (node);
    }
    node = tmp;
    while (tmp)
    {
        if (tmp->n == value)
        {
            next_node = tmp->next;
            free(tmp);
            node->next = next_node;
            return (head);
        }
        node = tmp;
        tmp = tmp->next;
    }
    return head;
}
typedef struct node_s
{
    int id;
    int deadline;   // like time_burnout
    struct node_s *next;
} node_t;

node_t *schedule(node_t *head, int id, int deadline, int mode)
{

}

int main()
{
    node_t *head;
    node_t *node1;
    node_t *node2;
    node_t *node3;

    node1 = create_node(1);
    node2 = create_node(3);
    node3 = create_node(4);

    head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    head = delete_value(head, 1);
    print_list(head);
    printf("len of nodes %d\n", len_of_nodes(head));
}