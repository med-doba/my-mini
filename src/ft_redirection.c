/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:50:16 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/16 00:01:00 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_r_input(char *file)
{
	close(gl.fd_in);
	gl.fd_in = open(file, O_RDONLY, 0666);
	if (gl.fd_in == -1)
		return (perror("open"), -1);
	return (0);
}

int	ft_r_output(char *file)
{
	close(gl.fd_out);
	gl.fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (gl.fd_out == -1)
		return (perror("open"), -1);
	return (0);
}

int	ft_append(char *file)
{
	close(gl.fd_out);
	gl.fd_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (gl.fd_out == -1)
		return (perror("open"), -1);
	return (0);
}

char	*ft_her_doc_util(char *tmp, char *ptr, t_env *env)
{
	t_env	*envhrd;

	envhrd = env;
	if (ft_find_char(tmp, '$') == 0)
		tmp = ft_parse_expand(tmp, envhrd);
	if (ft_find_staus(tmp) == 0)
		tmp = ft_expand_status(tmp);
	tmp = ft_strjoin(tmp, "\n");
	ptr = ft_strjoin(ptr, tmp);
	free(tmp);
	return (ptr);
}

int	ft_her_duc(char	*delimiter, t_env *env)
{
	char	*ptr;
	char	*tmp;

	ptr = ft_strdup("");
	unlink(".her_doc");
	gl.her_doc = 1;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strcmp(tmp, delimiter))
		{
			free(tmp);
			close(gl.fd_in);
			gl.fd_in = open(".her_doc", O_WRONLY | O_CREAT, 0666);
			if (gl.fd_in == -1)
				return (free(ptr), perror("open"), -1);
			ft_putstr_fd(ptr, gl.fd_in);
			close(gl.fd_in);
			gl.fd_in = open(".her_doc", O_RDONLY);
			return (free(ptr), 1);
		}
		ptr = ft_her_doc_util(tmp, ptr, env);
	}
	return (0);
}
