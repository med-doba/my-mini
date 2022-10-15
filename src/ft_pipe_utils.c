/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:00:39 by amasnaou          #+#    #+#             */
/*   Updated: 2022/10/15 23:01:05 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_pipe(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
}

int	**open_pipes(int **fd, int n)
{
	int	i;

	i = 0;
	fd = (int **)malloc(n * sizeof(int *));
	if (!fd)
		return (NULL);
	while (i < n)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (!fd)
			return (NULL);
		if (pipe(fd[i]) == -1)
			return (NULL);
		i++;
	}
	return (fd);
}

void	ft_run_redirection_in_pipe(t_lexer *lexer, t_env **env)
{
	t_lexer	*top;

	top = lexer;
	while (lexer && lexer->ch != '|')
	{
		if (lexer->ch == 'R')
		{
			if (ft_run_redirection(lexer, *env) == -1)
				return ;
		}
		lexer = lexer->next;
	}
}

void	wait_childs(int len)
{
	int	i;
	int	status;

	i = 0;
	waitpid(gl.pid, &status, 0);
	gl.st = WEXITSTATUS(status);
	while (i < len)
	{
		wait(NULL);
		i++;
	}
}
