/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:21:09 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/31 00:02:02 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_putnbr(int n)
{
    char base[] = "0123456789";
    if (n < 10)
    {
        write(1, &base[n], 1);
        return ;
    }
    if (n >= 10)
    {
        ft_putnbr(n / 10);
        write(1, &base[n % 10], 1);
    }
}

size_t  ft_strlen(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

void ft_putstr(char *s)
{
    if (!s)
        return ;
    write(1, s, ft_strlen(s));
}

int error_message(char *s)
{
    write(2, s, ft_strlen(s));
    return (1);
}

void    my_usleep(unsigned int n)
{
    int to_wait;

    to_wait = get_time() + n;
    while (get_time() < to_wait)
        usleep(10);
}
// int main(int argc, char **argv)
// {
//     ft_putnbr(atoi(argv[1]));
// }
