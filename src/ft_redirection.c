/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/13 16:24:45 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_run_redirection(t_lexer *lexer, t_env *env)
{
	char	*file;
	int		rtn;
	t_env	*env_her_doc;

	env_her_doc = env;
	file = lexer->next->content;
	rtn = 0;
	if (ft_strcmp(lexer->content, ">") == 0)
		rtn = ft_r_output(file);
	else if (ft_strcmp(lexer->content, ">>") == 0)
		rtn = ft_append(file);
	else if (ft_strcmp(lexer->content, "<") == 0)
		rtn = ft_r_input(file);
	else if (ft_strcmp(lexer->content, "<<") == 0)
		rtn = ft_her_duc(file, env_her_doc);
	if (rtn == -1)
		return (-1);
	return (0);
}

int	ft_r_input(char *file)
{
	close(gl.fd_in);
	if ((gl.fd_in = open(file, O_RDONLY, 0666)) == -1)
		return (perror("open"), -1);
	// dup2(gl.fd_file, 0);
	gl.fd_file = -1;
	return (0);
}

int	ft_r_output(char *file)
{
	close(gl.fd_out);
	if ((gl.fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		return (perror("open"), -1);
	// dup2(gl.fd_file, 1);
	// close(gl.fd_file);
	gl.fd_file = -2;

	return (0);
}

int	ft_append(char *file)
{
	close(gl.fd_out);
	if ((gl.fd_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		return (perror("open"), -1);
	// dup2(gl.fd_file, 1);
	// close(gl.fd_file);
	gl.fd_file = -2;

	return (0);
}

int	ft_her_duc(char	*delimiter, t_env *env)
{
	char	*ptr;
	char	*tmp;
	t_env	*envhrd;

	ptr = ft_strdup("");
	unlink("tmp");
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strcmp(tmp, delimiter))
		{
			free(tmp);
			close(gl.fd_in);
			if ((gl.fd_in = open("tmp", O_WRONLY | O_CREAT, 0666)) == -1)
				return (free(ptr), perror("open"), -1);
			gl.her_doc = 1;
			ft_putstr_fd(ptr, gl.fd_in);
			close(gl.fd_in);
			gl.fd_in = open("tmp", O_RDONLY);
			gl.fd_file = -1;
			return (free(ptr), 1);
		}
		envhrd = env;
		if (ft_find_char(tmp, '$') == 0)
			tmp = ft_parse_expand(tmp, envhrd);
		if (ft_find_staus(tmp) == 0)
			tmp = ft_expand_status(tmp);
		tmp = ft_strjoin(tmp, "\n");
		ptr = ft_strjoin(ptr, tmp);
		free(tmp);
	}
	return (0);
}
