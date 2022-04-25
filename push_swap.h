#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "stack_utils.h"

void swap(t_stacks *stackAB, int index)
{
    t_list * second;
    t_list * last;
    t_list * head;

    if (stackAB->lenght[index] > 1)
    {
        head = stackAB->stacks[index];
        second = stackAB->stacks[index]->next;
        if (stackAB->lenght[index] == 2)
            last = stackAB->stacks[index];
        else
            last = stackAB->stacks[index]->prev;

        last->next = second;
        second->next->prev = head;
        second->prev = last;
        if (stackAB->lenght[index] == 2)
            head->next = second;
        else
            head->next = second->next;
        second->next = head;
        head->prev = second;
        stackAB->stacks[index] = second;
    }
}

static void last_poped_element(t_stacks **stackAB, int pop, t_list ** head)
{
    t_list * empty;

    *head = (*stackAB)->stacks[pop];
    (*stackAB)->stacks[pop] = empty;
}

static void first_pushed_element(t_stacks *stackAB, int push, t_list * new)
{
    stackAB->stacks[push] = new;
    stackAB->stacks[push]->next = stackAB->stacks[push];
    stackAB->stacks[push]->prev = stackAB->stacks[push];
    stackAB->lenght[push]++;
}

static void other_poped_elements(t_stacks **stackAB, int pop, t_list ** head)
{
    t_list * last;
    t_list * second;

    last = (*stackAB)->stacks[pop]->prev;
    *head = (*stackAB)->stacks[pop];
    second = (*stackAB)->stacks[pop]->next;
    last->next = second;
    second->prev = last;
    (*stackAB)->stacks[pop] = second;
}

void push(t_stacks *stackAB, int push, int pop)
{
    t_list * head;

    if (stackAB->lenght[pop] > 0)
    {
        if (stackAB->lenght[pop] == 1)
            last_poped_element(&stackAB, pop, &head);
        else
        {
            other_poped_elements(&stackAB, pop, &head);

//            last = stackAB->stacks[pop]->prev;
//            head = stackAB->stacks[pop];
//            second = stackAB->stacks[pop]->next;
//            last->next = second;
//            second->prev = last;
//            stackAB->stacks[pop] = second;
        }
        if (stackAB->lenght[push] == 0)
            first_pushed_element(stackAB, push, head);
        else
        {
            head->next = stackAB->stacks[push];
            head->prev = stackAB->stacks[push]->prev;
            stackAB->stacks[push]->prev->next = head;
            stackAB->stacks[push]->prev = head;
            stackAB->lenght[push]++;
        }
        stackAB->lenght[pop]--;
    }
}

#endif //PUSH_SWAP_H
