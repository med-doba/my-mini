/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/10/13 09:31:53 by med-doba         ###   ########.fr       */
=======
/*   Updated: 2022/10/12 15:22:23 by med-doba         ###   ########.fr       */
>>>>>>> a720d58ce5eefc4df2b56434961722cd5fa7af8b
=======
/*   Updated: 2022/10/13 10:09:10 by med-doba         ###   ########.fr       */
>>>>>>> f694ddc4733f14e23dee4be36ac83eeefd590806
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
	close(gl.fd_file);
	return (0);
}

int	ft_r_output(char *file)
{
	if ((gl.fd_file = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		return (perror("open"), -1);
	dup2(gl.fd_file, 1);
	close(gl.fd_file);
	return (0);
}

int	ft_append(char *file)
{
	if ((gl.fd_file = open(file, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		return (perror("open"), -1);
	dup2(gl.fd_file, 1);
	close(gl.fd_file);
	return (0);
}

int	ft_her_duc(char	*delimiter)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strdup("");
	delimiter = ft_strjoin2(delimiter, "\n");
	while (1)
	{
<<<<<<< HEAD
		tmp = get_next_line(0);
=======
		tmp = readline("> ");
>>>>>>> f694ddc4733f14e23dee4be36ac83eeefd590806
		if (!tmp || !ft_strcmp(tmp, delimiter))
		{
			free(tmp);
			if ((gl.fd_file = open("tmp", O_WRONLY | O_CREAT, 0666)) == -1)
				return (free(ptr), perror("open"), -1);
			gl.her_doc = 1;
			ft_putstr_fd(ptr, gl.fd_file);
			close(gl.fd_file);
			gl.fd_file = open("tmp", O_RDONLY);
			dup2(gl.fd_file, 0);
			close(gl.fd_file);
			return (free(ptr), 1);
		}
		ptr = ft_strjoin(ptr, tmp);
		free(tmp);
	}
	return (0);
}
