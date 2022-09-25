/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:00:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 16:15:37 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_execution(t_lexer **lexer, t_env **env)
{
	while (*lexer)
	{
		if (ft_execution_up(lexer, env) == -1)
			return ;
		while (*lexer && (*lexer)->ch != '|')
			*lexer = (*lexer)->next;
		if (*lexer)
			*lexer = (*lexer)->next;
	}
}

int	ft_execution_up(t_lexer **lexer, t_env **env)
{
	t_lexer	*top;
	int		out;
	int		in;

	top = *lexer;
	out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	while (top && top->ch != '|')
	{
		if (top->ch == 'R')
			if (ft_run_redirection(top) == -1)
				return (-1);
		top = top->next;
	}
	if (ft_built_in(*lexer, *env) == -1)
		ft_execve(*lexer, *env);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
	return (0);
}

void	ft_execve(t_lexer *lexer, t_env *env)
{
	pid_t	pid;
	char	**arg_cmd;
	char	*path;

	arg_cmd = NULL;
	if ((path = ft_find_path(lexer->content, env)) == NULL)
		return (ft_putendl_fd("Error: command not found", 2));
	gl.sig = 1;
	if ((pid = fork()) == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		if (lexer && lexer->ch != '|' && lexer->ch != 'R')
			arg_cmd = ft_get_full_cmd(lexer);
		if (execve(path, arg_cmd, gl.arg_env) == -1)
			return (perror("execve"), ft_free_2d(arg_cmd), exit(127));
	}
	wait(NULL);
}

int	ft_nbr_of_pipes(t_lexer *lexer)
{
	int		pipe;
	t_lexer	*top;

	pipe = 0;
	top = lexer;
	while (top)
	{
		if (top->ch != '|')
			pipe++;
		top = top->next;
	}
	return (pipe);
}
