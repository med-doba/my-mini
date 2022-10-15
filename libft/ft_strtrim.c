/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:44:41 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/16 00:06:31 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		j;
	int		i;
	char	*hub;

	if (!s1 || !set)
		return (NULL);
	j = 0;
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	if (s1[i] == '\0')
	{
		free((void *)s1);
		hub = ft_strdup("");
		return (hub);
	}
	j = ft_strlen(s1);
	while (j != 0 && ft_strchr(set, s1[j - 1]))
		j--;
	hub = malloc(sizeof(char) * (j - i + 1));
	if (hub == NULL)
		return (NULL);
	ft_memcpy (hub, s1 + i, (j - i));
	hub[j] = '\0';
	return (free((void *)s1), hub);
}
