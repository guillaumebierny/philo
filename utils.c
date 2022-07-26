/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:21:09 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/27 00:10:17 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_putnbr(int n)
{
    char base[] = "0123456789";
    if (n < 10)
        write(1, &base[n], 1);
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
    while (s + i)
        i++;
    return (i);
}

void ft_putstr(char *s)
{
    if (!s)
        return ;
    write(1, s, ft_strlen(s));
}

ft_atoi()
{
    
}