/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:50:02 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/12 14:51:18 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

size_t	ft_strlen(char const	*str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}

void	*ft_memcpy(void *dest,	const void *src,	size_t size)
{
	char	*p1;
	char	*p2;
	int		i;

	p1 = dest;
	p2 = (char *)src;
	if (!p1 && !p2)
		return (NULL);
	i = 0;
	while (size != 0)
	{
		p1[i] = p2[i];
		i++;
		size--;
	}
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*hub;
	int		i;
	int		len;

	hub = NULL;
	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	hub = malloc(len + 1);
	if (hub == NULL)
	{
		free(hub);
		return (NULL);
	}
	while (src[i] != '\0')
	{
		hub[i] = src[i];
		i++;
	}
	hub[i] = '\0';
	return (hub);
}

// char	*ft_strjoin(char const *s1,	char const *s2)
// {
// 	char	*tab;
// 	size_t	i;
// 	size_t	j;
// 	int		k;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	k = i + j;
// 	tab = (char *)malloc(k + 1);
// 	if (tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0')
// 	{
// 		tab[i] = (char)s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 		tab[i++] = (char)s2[j++];
// 	tab[k] = '\0';
// 	free((char *)s1);
// 	return (tab);
// }
