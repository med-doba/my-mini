/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:17:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/12 14:49:00 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// char *get_next_line(int fd)
// {
// 	char buffer[2];
// 	char *line;

// 	if (fd < 0)
// 		return (NULL);
// 	line = (char *)malloc(sizeof(char) * 1);
// 	line[0] = '\0';
// 	// line = ft_strdup("");
// 	while (read(fd, buffer, 1) != 0)
// 	{
// 		if (buffer[0] == '\n')
// 		{
// 			// line = ft_strjoin(line, buffer);
// 			return (line);
// 		}
// 		else
// 			line = ft_strjoin(line, buffer);
// 	}
// 	if (line[0] != '\0')
// 		return (line /*ft_strjoin(line,"\n")*/);
// 	return (free(line), NULL);
// }

// char	*get_next_line(int fd)
// {
// 	char	tmp[800000];
// 	char	buff[0];
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	tmp[0] = '\0';
// 	while (read(fd, buff, 1) == 1)
// 	{
// 		tmp[i] = buff[0];
// 		tmp[i + 1] = '\0';
// 		if (tmp[i] == '\n')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (tmp[0] == '\0')
// 		return (NULL);
// 	line = (char *)malloc((i + 1) * sizeof(char));
// 	if (!line)
// 		return (NULL);
// 	ft_memmove(line, tmp, strlen(tmp));
// 	return (line[i + 1] = '\0', line);
// }
