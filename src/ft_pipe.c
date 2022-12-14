/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:55:46 by amasnaou          #+#    #+#             */
/*   Updated: 2022/10/16 12:05:37 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_execute_pipe(t_lexer *lexer, t_env **env, int n)
{
	int			**fd;
	int			i;

	i = 0;
	fd = open_pipes(n);
	if (fd == NULL)
		return ;
	while (lexer)
	{
		dup_for_pipe(fd, &i, n);
		ft_run_redirection_in_pipe(lexer, env);
		command_fork(lexer, env, fd, n);
		while (lexer && (lexer)->ch != '|')
			lexer = (lexer)->next;
		if (lexer)
			lexer = (lexer)->next;
		i++;
	}
	close_pipe(fd, n);
	wait_childs(n);
	ft_free_2d_fd(fd);
}

void	command_fork(t_lexer *top, t_env **env, int **fd, int n)
{
	gl.sig = 1;
	gl.pid = fork();
	if (gl.pid == -1)
		return (perror("fork pipe"));
	if (gl.pid == 0)
	{
		dup2(gl.fd_in, 0);
		dup2(gl.fd_out, 1);
		close_pipe(fd, n);
		close(gl.fd_in);
		close(gl.fd_out);
		if (ft_execution_up(&top, env) == -1)
			return (exit(1));
		exit(0);
	}
	close(gl.fd_in);
	close(gl.fd_out);
}

void	dup_for_pipe(int **fd, int *i, int n)
{
	gl.fd_out = dup(STDOUT_FILENO);
	gl.fd_in = dup(STDIN_FILENO);
	if (*i < n)
	{
		close(gl.fd_out);
		gl.fd_out = dup(fd[*i][1]);
		close(fd[*i][1]);
	}
	if (*i != 0)
	{
		close(gl.fd_in);
		gl.fd_in = dup(fd[*i - 1][0]);
		close(fd[*i - 1][0]);
	}
}
