/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:36:33 by med-doba          #+#    #+#             */
/*   Updated: 2022/08/29 19:22:41 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_find_staus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_expand_status(char *str)
{
	char	*status;
	char	*rtn;
	char	*tmp;
	int		i;

	i = 0;
	status = ft_itoa(var.st);
	rtn = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			i++;
			rtn = ft_strjoin(rtn, status);
			i++;
		}
		else
		{
			tmp = ft_char_to_str(str[i]);
			rtn = ft_strjoin(rtn, tmp);
			free(tmp);
			i++;
		}
	}
	return (free(status), free(str), rtn);
}
