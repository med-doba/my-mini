/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:55:46 by amasnaou          #+#    #+#             */
/*   Updated: 2022/10/15 18:16:35 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void close_pipe(int fd[][2], int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
}

void	wait_childs(int len, int pid)
{
	int	i;
	// int status;

	i = 0;
	while (i < len)
	{
		wait(NULL);
		// waitpid(pid,&status,0);
		i++;
	}
	gl.st = WEXITSTATUS(pid);
}

void open_pipes(int fd[][2], int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		if (pipe(fd[i]) == -1)
			return ;
		i++;
	}
}

void    ft_execute_pipe(t_lexer *lexer, t_env **env, int n)
{
	int			fd[n][2];
	int			i;
	int			in;
	int			out;
	int			status;
	t_lexer		*top;
	t_lexer		*top1;

	open_pipes(fd, n);
	i = 0;
	top = lexer;
	out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	while(top)
	{
		gl.fd_out = dup(STDOUT_FILENO);
		gl.fd_in = dup(STDIN_FILENO);
		if (i < n)
		{
			close(gl.fd_out);
			gl.fd_out = dup(fd[i][1]);
			close(fd[i][1]);
		}
		if (i != 0)
		{
			close(gl.fd_in);
			gl.fd_in = dup(fd[i - 1][0]);
			close(fd[i - 1][0]);
		}
		top1 = top;
		while (top1 && top1->ch != '|')
		{
			if (top1->ch == 'R')
			{
				if (ft_run_redirection(top1, *env) == -1)
				return ;
			}
			top1 = top1->next;
		}
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
			if (gl.her_doc == 1)
				unlink(".her_doc");
			if (lexer != NULL)
				exit(0);
		}
		close(gl.fd_in);
		close(gl.fd_out);
		while (top && (top)->ch != '|')
			top = (top)->next;
		if (top)
			top = (top)->next;
		i++;
	}
	close_pipe(fd, n);
	close(out);
	close(in);
	waitpid(gl.pid,&status,0);
	gl.st = WEXITSTATUS(status);
	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
}
