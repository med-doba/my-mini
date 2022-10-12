/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/12 15:22:23 by med-doba         ###   ########.fr       */
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
		file = ft_strjoin2(file, "\n");
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
	char	*tmp;

	ptr = ft_strdup("");
	while (1)
	{
		tmp = get_next_line(0);
		// printf("befor = %s", tmp);
		if (!tmp || !ft_strcmp(tmp, delimiter))
		{
			// printf("delimeteur = %s", tmp);
			free(tmp);
			tmp = ptr;
			if ((gl.fd_file = open("tmp", O_WRONLY | O_CREAT, 0645)) == -1)
				return (free(ptr), perror("open"), -1);
			gl.her_doc = 1;
			ft_putendl_fd(tmp, gl.fd_file);
			dup2(gl.fd_file, 0);
			return (free(tmp), 1);
		}
		ptr = ft_strjoin(ptr, tmp);
		free(tmp);
	}
	return (0);
}
