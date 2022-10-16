/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:00:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/16 09:45:26 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_execution(t_lexer *lexer, t_env **env)
{
	int	pipe;

	pipe = ft_nbr_of_pipes(lexer);
	if (pipe == 0)
	{
		if (lexer)
		{
			if (ft_execution_one_commande(lexer, env) == -1)
				return ;
			if (gl.her_doc == 1)
				unlink(".her_doc");
		}
	}
	else
	{
		ft_execute_pipe(lexer, env, pipe);
		if (gl.her_doc == 1)
			unlink(".her_doc");
	}
}

int	ft_execution_one_commande(t_lexer *lexer, t_env **env)
{
	t_lexer	*top;
	int		out;
	int		in;

	top = lexer;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	gl.fd_out = dup(STDOUT_FILENO);
	gl.fd_in = dup(STDIN_FILENO);
	while (top && top->ch != '|')
	{
		if (top->ch == 'R')
			if (ft_run_redirection(top, *env) == -1)
				return (-1);
		top = top->next;
	}
	dup2(gl.fd_in, 0);
	dup2(gl.fd_out, 1);
	while (lexer && (lexer)->ch == 'R' && (lexer)->ch != '|')
		lexer = (lexer)->next->next;
	if (lexer && (lexer)->ch != '|' && ft_built_in(lexer, env) == -1)
		ft_execve_one_commande(lexer, *env);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	return (close(out), close(in), 0);
}

void	ft_execve_one_commande(t_lexer *lexer, t_env *env)
{
	pid_t	pid;
	char	**arg_cmd;
	char	*path;
	int		status;

	arg_cmd = NULL;
	path = ft_find_path(lexer->content, env);
	if (path == NULL)
		return (gl.st = 127, ft_putendl_fd("Error: command not found", 2));
	gl.sig = 1;
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		if (lexer && lexer->ch != '|' && lexer->ch != 'R')
			arg_cmd = ft_get_full_cmd(lexer);
		gl.arg_env = convert_list(env);
		if (gl.arg_env == NULL)
			return (perror("malloc"), ft_free_2d(arg_cmd), exit(127));
		if (execve(path, arg_cmd, gl.arg_env) == -1)
			return (perror("execve"), ft_free_2d(arg_cmd), exit(127));
	}
	waitpid(pid, &status, 0);
	return (gl.st = WEXITSTATUS(status), free(path));
}

int	ft_execution_up(t_lexer **lexer, t_env **env)
{
	while (*lexer && (*lexer)->ch == 'R' && (*lexer)->ch != '|')
		*lexer = (*lexer)->next->next;
	if ((*lexer)->ch != '|' && ft_built_in(*lexer, env) == -1)
		ft_execve(*lexer, *env);
	if (gl.her_doc == 1)
		unlink(".her_doc");
	if (gl.st != 0)
		exit(gl.st);
	return (0);
}

void	ft_execve(t_lexer *lexer, t_env *env)
{
	char	**arg_cmd;
	char	*path;

	arg_cmd = NULL;
	path = ft_find_path(lexer->content, env);
	if (path == NULL || lexer->content[0] == '\0')
		return (gl.st = 127, ft_putendl_fd("Error: command not found", 2));
	if (lexer && lexer->ch != '|' && lexer->ch != 'R')
		arg_cmd = ft_get_full_cmd(lexer);
	gl.arg_env = convert_list(env);
	if (gl.arg_env == NULL)
		return (perror("malloc"), ft_free_2d(arg_cmd), free(path), exit(127));
	if (execve(path, arg_cmd, gl.arg_env) == -1)
		return (gl.st = 127, perror("execve"), free(path), ft_free_2d(arg_cmd));
	free(path);
}
