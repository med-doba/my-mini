/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:17:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/12 21:43:35 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// char *get_next_line(int fd)
// {
// 	char buffer[2];
// 	char *line;

// 	if (fd < 0)
// 		return (NULL);
// 	// line = (char *)malloc(sizeof(char) * 1);
// 	// line[0] = '\0';
// 	line = ft_strdup("");
// 	while (read(fd, buffer, 1) != 0)
// 	{
// 		if (buffer[0] == '\n')
// 		{
// 			line = ft_strjoin2(line, buffer);
// 			return (line);
// 		}
// 		else
// 			line = ft_strjoin2(line, buffer);
// 	}
// 	if (line[0] != '\0')
// 		return (ft_strjoin2(line,"\n"));
// 	return (free(line), NULL);
// }