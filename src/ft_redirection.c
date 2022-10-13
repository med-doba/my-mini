/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/13 09:31:53 by med-doba         ###   ########.fr       */
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
	{
		// file = ft_strjoin(file, "\n");
		rtn = ft_her_duc(file);
	}
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
	char	*ptr;

	ptr = ft_strdup("");
	while (1)
	{
		gl.herdoc = readline("> ");
		if (!gl.herdoc || !ft_strcmp(gl.herdoc, delimiter))
		{
			gl.herdoc = ptr;
			if ((gl.fd_file = open(".her_doc", O_RDWR | O_CREAT, 0777)) == -1)
				return (free(ptr), perror("open"), -1);
			gl.her_doc = 1;
			ft_putendl_fd(gl.herdoc, gl.fd_file);
			close(gl.fd_file);
			gl.fd_file = open(".her_doc", O_RDWR | O_CREAT, 0777);
			dup2(gl.fd_file, 0);
			close(gl.fd_file);
			return (free(ptr), 1);
		}
		ptr = ft_strjoin(ptr, gl.herdoc);
		free(gl.herdoc);
	}
	return (0);
}
