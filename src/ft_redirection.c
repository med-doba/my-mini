/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/11 12:57:04 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_run_redirection(t_lexer *lexer)
{
	char	*file;
	int		rtn;

	file = lexer->next->content;
	rtn = 0;
	if (ft_strcmp(lexer->content, ">") == 0)
		rtn = ft_r_output(file);
	else if (ft_strcmp(lexer->content, ">>") == 0)
		rtn = ft_append(file);
	else if (ft_strcmp(lexer->content, "<") == 0)
		rtn = ft_r_input(file);
	else if (ft_strcmp(lexer->content, "<<") == 0)
		rtn = ft_her_duc(file);
	if (rtn == -1)
		return (-1);
	return (0);
}

int	ft_r_input(char *file)
{
	if ((gl.fd_file = open(file, O_RDONLY, 0666)) == -1)
		return (perror("open"), -1);
	dup2(gl.fd_file, 0);
	return (0);
}

int	ft_r_output(char *file)
{
	if ((gl.fd_file = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		return (perror("open"), -1);
	dup2(gl.fd_file, 1);
	return (0);
}

int	ft_append(char *file)
{
	if ((gl.fd_file = open(file, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		return (perror("open"), -1);
	dup2(gl.fd_file, 1);
	return (0);
}

int	ft_her_duc(char	*delimiter)
{
	// int		fd;
	// char	*line;
	char	*ptr;
	int 	condition;


	// if (unlink(".her_doc"))
		// if ((gl.fd_file = open(".her_doc", O_RDWR | O_CREAT, 0666)) == -1)
		// 	return (perror("open"), -1);
	gl.her_doc = 1;
	condition = 0;
	ptr = ft_strdup("");
	while (1)
	{
		// line = readline("> ");
		gl.herdoc = readline("> ");
		// if (!line || !ft_strcmp(line, delimiter))
		// 	return (free(line), 0);
		if (!gl.herdoc || !ft_strcmp(gl.herdoc, delimiter))
		{
			gl.herdoc = ptr;
			if ((gl.fd_file = open(".her_doc", O_RDWR | O_CREAT, 0666)) == -1)
				return (perror("open"), -1);
			ft_putendl_fd(gl.herdoc, gl.fd_file);
			return (free(gl.herdoc), 0);
		}
		if (condition == 1)
			ptr = ft_strjoin(ptr, "\n");
		ptr = ft_strjoin(ptr, gl.herdoc);
		condition = 1;
		// ft_putendl_fd(line, gl.fd_file);
		// free(line);
		free(gl.herdoc);
	}
	// printf("hna %s\n", ptr);
	// gl.herdoc = ptr;
	return (0);
}
