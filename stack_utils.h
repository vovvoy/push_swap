#ifndef STACK_UTILS_H
#define STACK_UTILS_H


#include <stdlib.h>

typedef struct      s_list
{
    int             data;
    struct s_list   *next;
    struct s_list   *prev;
}                   t_list;

typedef struct      s_best_move
{
//    int             a_id;
//    int             b_id;
    int             moves[7];
}                   t_bmove;

typedef struct      s_stacks
{
    t_list          *stacks[2];
    int             lenght[2];
    int             max_min[2];
//    int             moves[7];
}                   t_stacks;

t_list * new_node(int data)
{
    t_list* new = (t_list*) malloc(sizeof(t_list));
    new->data = data;
    new->next = new;
    new->prev = new;
    return new;
}

void fill_stack(t_stacks *stackAB, int data, int index)
{
    t_list * stackNew = new_node(data);
    if (stackAB->lenght[index] == 0)
    {
        stackAB->stacks[index] = stackNew;
        stackAB->lenght[index]++;
    }
    else
    {
        t_list * stackLast = stackAB->stacks[index]->prev;
        stackLast->next = stackNew;
        stackAB->stacks[index]->prev = stackNew;
        stackNew->next = stackAB->stacks[index];
        stackNew->prev = stackLast;
        stackAB->stacks[index] = stackNew;
        stackAB->lenght[index]++;
    }
}


#endif