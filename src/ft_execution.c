/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:00:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/23 13:18:16 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	 ft_execution(t_lexer **lexer, t_env **env)
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

int		ft_execution_up(t_lexer **lexer, t_env **env)
{
	int		out;
	int		in;
	t_lexer *top;

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

// char	**ft_get_env_2d(t_env *env)
// {
// 	char	**ptr;

// 	while (env)
// 	{
// 		/* code */
// 	}

// }

void	ft_execve(t_lexer *lexer, t_env *env)
{
	int		pid;
	char	**arg_cmd;
	char	*path;

	arg_cmd = NULL;
	if ((path  = ft_find_path(lexer->content, env)) == NULL)
		return (ft_putendl_fd("Error: command not found", 2));
	if ((pid = fork()) == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		if (lexer && lexer->ch != '|' && lexer->ch != 'R')
			arg_cmd = ft_get_full_cmd(lexer);
		if (execve(path, arg_cmd, var.arg_env) == -1)
		{
			return (ft_free_2d(arg_cmd), perror("execve"), exit(127));
		}
	}
	wait(NULL);
}

char	**ft_get_full_cmd(t_lexer *lexer)
{
	char	*ptr;
	char	*tmp;
	char	**two;

	tmp = ft_strdup("");
	ptr = ft_strdup("");
	while (lexer && lexer->ch != '|' && lexer->ch != 'R')
	{
		tmp = ft_strjoin(lexer->content, ";");
		ptr = ft_strjoin(ptr, tmp);
		free(tmp);
		lexer = lexer->next;
	}
	two = ft_split(ptr, ';');
	return (free(ptr), free(tmp), two);
}

char	*ft_find_path(char *cmd, t_env *env)
{
	int		i;
	char	*path;
	char	**ptr;
	char	*str;

	i = 0;
	path = NULL;
	str = NULL;
	//absolute path
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	//relative path
	////find $PATH///
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			path = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	ptr = ft_split(path, ':');
	free(path);
	while (ptr[i])
	{
		ptr[i] = ft_strjoin(ptr[i], "/");
		ptr[i] = ft_strjoin(ptr[i], cmd);
		if (access(ptr[i], F_OK | X_OK) == 0)
		{
			str = ft_strdup(ptr[i]);
			ft_free_2d(ptr);
			return (str);
		}
		i++;
	}
	return (ft_free_2d(ptr), NULL);
}

int	ft_nbr_of_pipes(t_lexer *lexer)
{
	int		pipe;
	t_lexer	*top;

	pipe = 0;
	top = lexer;
	while(top)
	{
		if(top->ch != '|')
			pipe++;
		top = top->next;
	}
	return (pipe);
}
