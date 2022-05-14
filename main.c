#include <unistd.h>
#include "push_swap.h"

void ft_putnbr(int nb){
    int a;

    if (nb == -2147483648)
        write(1, "-2147483648", 11);
    else if (nb > 0 && nb < 10)
    {
        a = nb + 48;
        write(1, &a, 1);
    }
    else if (nb == 0)
        write(1, "0", 1);
    else if(nb < 0)
    {
        write(1, "-", 1);
        ft_putnbr(-nb);
    }
    else if (nb > 0)
    {
        a = nb % 10 + 48;
        ft_putnbr(nb / 10);
        write(1, &a, 1);
    }
}

int  ft_atoi(char *argument){
    long long n;
    int sign;

    n = 0;
    sign = 1;
    while(*argument)
    {
        if (*argument == '-')
            sign = -1;
        else
            n = n * 10 + *argument - 48;
        if ((n > 2147483647 && sign == 1) || (n < -2147483648 && sign == -1))
        {
            write(1, "Error:\n\tNon integer argument found!", 35);
            exit(1);
        }
        argument++;
    }
    return (int)(n * sign);
}

void ft_isduplicate(int *arr, int number)
{
    unsigned int i;

    i = number;
    if (arr[i] == 1)
    {
        write(1, "Error:\n\tDuplicate arguments found!", 33);
        exit(1);
    }
    arr[i] = 1;
}

void ft_isdigit(int len, char **arguments, t_stacks *stackAB){
    unsigned int i;
    char * copy_argument;
//    int arr[4294967295];
    int arr[2147];
    int arg;

    i = 0;
    while (++i < len)
    {
        copy_argument = arguments[i];
        if (*copy_argument == '-')
            copy_argument++;
        while (*copy_argument)
        {
            if (*copy_argument - 48 < 0 || *copy_argument - 48 > 9)
            {
                write(1, "Error:\n\tNon digit argument found!", 33);
                exit(1);
            }
            copy_argument++;
        }
        arg = ft_atoi(arguments[i]);
//        ft_isduplicate(arr, arg);
        fill_stack(stackAB, arg, 0);
    }
}

int ft_num_len(int number)
{
    int tmp;
    int len;

    if (number < 0)
    {
        number = -number;
        len = 2;
    }
    else
        len = 1;
    tmp = number;
    while (tmp / 10)
    {
        tmp = tmp / 10;
        len++;
    }
    return (len);
}

void ft_tree_elem(t_stacks *stackAB)
{
    int a[3];

    while(1)
    {
        a[0] = stackAB->stacks[0]->data;
        a[1] = stackAB->stacks[0]->next->data;
        a[2] = stackAB->stacks[0]->prev->data;
        if ((a[2] > a[1] && a[2] > a[0] && a[0] > a[1]) ||
            (a[0] > a[1] && a[0] > a[2] && a[1] > a[2]) ||
            (a[1] > a[2] && a[1] > a[0] && a[2] > a[0]))
        {
            swap(stackAB, 0);
            write(1, "sa\n", 3);
        }
        else if (a[1] > a[0] && a[1] > a[2] && a[0] > a[2])
        {
            rotate_or_reverse_rotate(stackAB, 0, '-');
            write(1, "rra\n", 4);
        }
        else if (a[0] > a[1] && a[0] > a[2]  && a[2] > a[1])
        {
            rotate_or_reverse_rotate(stackAB, 0, '+');
            write(1, "ra\n", 3);
        }
        else
            break;
    }
}

void ft_two_elem(t_stacks *stackAB)
{
    if (stackAB->stacks[0]->data > stackAB->stacks[0]->next->data)
    {
        rotate_or_reverse_rotate(stackAB, 0, '+');
        write(1, "ra\n", 3);
    }
}

void ft_best_move(t_stacks *stackAB)
{


}

void ft_print_whitespace(int len, int number)
{
    char whitespace[len];
    int index;

    index = 0;
    while(index < len)
        whitespace[index++] = ' ';
    ft_putnbr(number);
    write(1, whitespace, len);
}

void ft_before_print_stack(t_stacks *stackAB, t_list **tmpA, t_list **tmpB, int *dif)
{
    if (stackAB->lenght[0] > stackAB->lenght[1])
    {
        *tmpA = stackAB->stacks[0];
        *tmpB = stackAB->stacks[1];
        *dif = stackAB->lenght[0] - stackAB->lenght[1];
    }
    else
    {
        *tmpA = stackAB->stacks[1];
        *tmpB = stackAB->stacks[0];
        *dif = stackAB->lenght[1] - stackAB->lenght[0];
    }
}

void ft_print_stack(t_stacks *stackAB, int index)
{
    t_list *tmpA;
    t_list *tmpB;
    int dif;

    ft_before_print_stack(stackAB, &tmpA, &tmpB, &dif);
    while (1)
    {
        ft_print_whitespace(15 - ft_num_len(tmpA->data), tmpA->data);
        if (dif < 1)
        {
            ft_putnbr(tmpB->data);
            tmpB = tmpB->next;
        }
        write(1, "\n", 1);
        tmpA = tmpA->next;
        dif--;
        if (tmpA == stackAB->stacks[index])
            break;
    }
    write(1, "-----------------------------\n", 30);
    write(1, "stack A        stack B", 22);
}

int main(int argc, char** argv)
{
    t_stacks stackAB;

    stackAB.lenght[0] = 0;
    stackAB.lenght[1] = 0;
    if (argc > 1){
        ft_isdigit(argc, argv, &stackAB);
        push(&stackAB, 1, 0);
        ft_two_elem(&stackAB);
        write(1, "-----------------------------\n", 30);
        ft_print_stack(&stackAB, 0);

    }

    return (0);
}

//54 634 546 23