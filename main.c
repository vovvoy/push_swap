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

void ft_isdigit(int len, char **arguments, t_stacks *stackAB){
    unsigned int i;
    char * copy_argument;

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
        fill_stack(stackAB, ft_atoi(arguments[i]), 0);
    }
}

int main(int argc, char** argv)
{
    t_stacks stackAB;

    stackAB.lenght[0] = 0;
    stackAB.lenght[1] = 0;
    if (argc > 1){
        ft_isdigit(argc, argv, &stackAB);
//        swap(&stackAB, 0);
		rotate_or_reverse_rotate(&stackAB, 0, '+');
		
        push(&stackAB, 1, 0);
        push(&stackAB, 1, 0);
        push(&stackAB, 0, 1);
        push(&stackAB, 0, 1);
    }
    return (0);
}

//54 634 546 23