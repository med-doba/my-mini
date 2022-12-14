/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:49:30 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/10 21:26:30 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(char *str)
{
	int		j;
	long	nb;
	long	f;

	j = 0;
	nb = 1;
	f = 0;
	while (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'
		|| str[j] == '\r' || str[j] == '\v' || str[j] == '\f')
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			nb *= -1;
		j++;
	}
	while (str[j] >= '0' && str[j] <= '9')
	{
		f = (f * 10) + str[j] - 48;
		j++;
	}
	return (f * nb);
}
