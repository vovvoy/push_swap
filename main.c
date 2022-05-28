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

void moves_default_value(int **moves)
{
    int i;

    i = 0;
    *(moves + 0) = 2147483647;
    while (++i < 7)
        *(moves + i) = 0;
}

int ft_best_move_in_a(t_stacks *stackAB, int target)
{
    int closest_max;
    t_list *tmp;
    int ret_val;
    int i;

    i = 0;
    closest_max = -2147483648;
    tmp = stackAB->stacks[0];
    while (i < stackAB->lenght[0])
    {
        if (target > stackAB->max_min[0] && tmp->data == stackAB->max_min[1])
            return i;
        else if (target < stackAB->max_min[1] && tmp->data == stackAB->max_min[0])
            return i;
        else if (tmp->data < target && tmp->data >= closest_max)
        {
            closest_max = tmp->data;
            ret_val = i;
        }
        i++;
        tmp = tmp->next;
    }
    return ret_val;
}

int max(int a, int b, int **moves, int index)
{
    moves_default_value(moves);
    if (a > b)
    {
        if (index) {
            *(moves + 4) = a - b;
            *(moves + 6) = b;
        }
        else
        {
            *(moves + 1) = a - b;
            *(moves + 3) = b;
        }
        return a;
    }
    if (index)
    {
        *(moves + 5) = b - a;
        *(moves + 6) = a;
    }
    else
    {
        *(moves + 2) = b - a;
        *(moves + 3) = a;
    }
    return b;
}

int  ft_count_move(t_stacks *stackAB, int a, int b, int **moves)
{
    int mid_a;
    int mid_b;

    mid_a = (stackAB->lenght[0] + 1) / 2;
    mid_b = (stackAB->lenght[1] + 1) / 2;
    if (mid_a > a && mid_b > b && *(moves + 0) > max(a, b,moves, 0))
        return max(a, b,moves, 0);
    else if (mid_a <= a && mid_b <= b && *(moves + 0) > max(stackAB->lenght[0] - a, stackAB->lenght[1] - b, moves, 1))
        return max(stackAB->lenght[0] - a, stackAB->lenght[1] - b, moves, 1);
    else if (mid_a > a && mid_b <= b && *(moves + 0) > (a + stackAB->lenght[1] - b))
    {
        moves_default_value(moves);
        *(moves + 4) = a;
        *(moves + 2) = stackAB->lenght[1] - b;
        return (a + stackAB->lenght[1] - b);
    }
    else if (mid_a <= a && mid_b > b && *(moves + 0) > (stackAB->lenght[0] - a + b))
    {
        moves_default_value(moves);
        *(moves + 1) = a;
        *(moves + 5) = b;
        return (stackAB->lenght[0] - a + b);
    }
}

void ft_best_move_in_b(t_stacks *stackAB)
{
    t_list * rotate_tmp;
    int move;
    int **moves;
    int a_id;
    int index;

    index = 0;
    moves = (int**)malloc(sizeof(int*));
    moves[0] = (int*)malloc(sizeof(int));
    rotate_tmp = stackAB->stacks[1];
    moves_default_value(moves);
    while (index < stackAB->lenght[1])
    {
        a_id = ft_best_move_in_a(stackAB, rotate_tmp->data);
        ft_count_move(stackAB, a_id, index, moves);
        rotate_tmp = rotate_tmp->next;
        index++;
    }
    ft_putnbr(*(moves + 4));
}

void ft_print_whitespace(int len, int number, int id)
{
    char whitespace[len];
    int index;

    index = 0;
    while(index < len)
        whitespace[index++] = ' ';
	if (id == 1)
		write(1, whitespace, len);
	
	ft_putnbr(number);
	if (id == 0)
		write(1, whitespace, len);
	if (id == 1)
		write(1, "\n", 1);
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

void ft_print_stack(t_stacks *stackAB)
{
    t_list *tmp[2];
    int dif;

    tmp[0] = stackAB->stacks[0];
	tmp[1] = stackAB->stacks[1];
	dif = stackAB->lenght[0] - stackAB->lenght[1];
    while (1)
    {
		if (dif < 0)
		{
			ft_print_whitespace(15, tmp[1]->data, 1);
			tmp[1] = tmp[1]->next;
			dif++;
			continue;
		}
		else if (dif > 0)
		{
			ft_print_whitespace(15 - ft_num_len(tmp[0]->data), tmp[0]->data, 0);
			tmp[0] = tmp[0]->next;
			dif--;
			continue;
		}
		else
		{
			ft_print_whitespace(15 - ft_num_len(tmp[0]->data), tmp[0]->data, 0);
			ft_print_whitespace(0, tmp[1]->data, 1);
			tmp[0] = tmp[0]->next;
			tmp[1] = tmp[1]->next;
		}
		if (tmp[0] == stackAB->stacks[0] && tmp[1] == stackAB->stacks[1])
			break;
    }
    write(1, "-----------------------------\n", 30);
    write(1, "stack A        stack B\n", 23);
}

void find_max_min(t_stacks *stackAB)
{
    static int max_min[2];
    t_list *tmpA;

    stackAB->max_min[0] = -2147483648;
    stackAB->max_min[1] = 2147483647;
    tmpA = stackAB->stacks[0];
    while (1)
    {
        if (stackAB->max_min[0] < tmpA->data)
            stackAB->max_min[0] = tmpA->data;
        if (stackAB->max_min[1] > tmpA->data)
            stackAB->max_min[1] = tmpA->data;
        tmpA = tmpA->next;
        if (tmpA == stackAB->stacks[0])
            break;
    }
}

void rotate(t_stacks *stackAB, int index)
{
    while (index > 0 && index < stackAB->lenght[0])
        if (stackAB->lenght[0] / 2 >= index)
        {
            rotate_or_reverse_rotate(stackAB, 0, '+');
            write(1, "ra\n", 3);
            index--;
        }
        else
        {
            rotate_or_reverse_rotate(stackAB, 0, '-');
            write(1, "rra\n", 4);
            index++;
        }
    swap(stackAB, 0);
    write(1, "sa\n", 3);
}

int issorted(t_stacks *stackAB, int i, int max)
{
    t_list *tmp;

    tmp = stackAB->stacks[i];
    while(1)
    {
        if (tmp->data > tmp->next->data && tmp->data != max)
            return 0;
        tmp = tmp->next;
        if (tmp == stackAB->stacks[0])
            break;
    }
    return 1;
}

void sort_five_less_stack(t_stacks *stackAB)
{
    t_list *tmp;
    int i;

    i = 0;
    find_max_min(stackAB);
    tmp = stackAB->stacks[0];
    while (1)
    {
        if (tmp->data > tmp->next->data && tmp->data != stackAB->max_min[0] /*&& tmp->next->data == max_min[1]*/)
        {
            rotate(stackAB, i);
            i = 1;
            continue;
        }
        if (issorted(stackAB, 0, stackAB->max_min[0]))
        {

            break;
        }
        tmp = tmp->next;
        i++;
        if (tmp == stackAB->stacks[0])
            i = 0;
    }
}

void move_all_to_stack_b(t_stacks *stackAB)
{
    while (stackAB->lenght[0] > 5)
    {
        push(stackAB, 1, 0);
        write(1, "pb\n", 3);
    }
    sort_five_less_stack(stackAB);
}

int main(int argc, char** argv)
{
    t_stacks stackAB;

    stackAB.lenght[0] = 0;
    stackAB.lenght[1] = 0;
    if (argc > 1){
        ft_isdigit(argc, argv, &stackAB);
        move_all_to_stack_b(&stackAB);
        ft_best_move_in_b(&stackAB);
//        push(&stackAB, 1, 0);
//        ft_two_elem(&stackAB);
        write(1, "-----------------------------\n", 30);
        ft_print_stack(&stackAB);

    }

    return (0);
}
