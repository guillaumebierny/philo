/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:26:17 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/27 16:26:31 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_number(char *str, int *i, long int res, int *signe)
{
	while (str[*i] >= 48 && str[*i] <= 57)
	{
		res = res * 10 + (str[*i] - 48);
		(*i)++;
		if (res < 0 && (*signe) == -1)
			return (0);
		else if (res < 0 && (*signe) == 1)
			return (-1);
	}
	return (res);
}

static int	get_sign(char *str, int *i, int signe, int count)
{
	while (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			signe *= -1;
		if (++count > 1)
			return (0);
		(*i)++;
	}
	return (signe);
}

int	ft_atoi(char *str)
{
	int			i;
	int			signe;
	int			count;
	long int	res;

	res = 0;
	count = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	signe = get_sign((char *)str, &i, signe, count);
	if (signe == 0)
		return (0);
	res = count_number((char *)str, &i, res, &signe);
	if (res == 0)
		return (0);
	else if (res == -1)
		return (-1);
	else
		return ((res * signe));
}
