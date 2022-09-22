/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/22 22:01:13 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_run_redirection(t_lexer *lexer)
{
	char	*file;
	int 	fd;

	file = lexer->next->content;
	if (ft_strcmp(lexer->content, ">") == 0)
	{
		if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 00777)) == -1)
			return (perror("open"), -1);
		dup2(fd, 1);
	}
	else if (ft_strcmp(lexer->content, ">>") == 0)
	{
		if ((fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777)) == -1)
			return (perror("open"), -1);
		dup2(fd, 1);
	}
	else if (ft_strcmp(lexer->content, "<") == 0)
	{
		if ((fd = open(file, O_RDONLY, 0777)) == -1)
			return (perror("open"), -1);
		dup2(fd, 0);
	}
	// else if (ft_strcmp(lexer->content, "<<") == 0)
	// {
	// 	if ((fd = open(file, O_RDWR | O_CREAT, 0777)) == -1)
	// 		return (perror("open"));
	// }
	return (0);
}

// void	ft_r_input()
// {

// }

// void	ft_r_output(char *file)
// {
// 	int fd;

// 	if ((fd = open(file, O_RDWR | O_CREAT, 0777)) == -1)
// 		return (perror("open"));

// }

// void	ft_append()
// {

// }

// void	ft_her_duc()
// {

// }
