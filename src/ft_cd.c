/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:20:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/17 17:54:56 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_cd(t_lexer *lexer, t_env **env)
{
	char	oldcwd[1024];
	char	cwd[1024];

	getcwd(oldcwd, 1024);
	lexer = lexer->next;
	if (!lexer || lexer->ch == '|')
		return (gl.st = 1, ft_cd_to_home(env, oldcwd));
	else if (lexer)
	{
		while (lexer && lexer->ch != '|')
		{
			if (lexer->ch != 'R')
			{
				if (lexer->content[0] != '\0')
					if (chdir(lexer->content) == -1)
						return (gl.st = 1, perror("chdir"));
				if (getcwd(cwd, 1024) == NULL)
					perror("getcwd");
				ft_change_pwd_oldpwd(env, oldcwd);
				break ;
			}
			lexer = lexer->next->next;
		}
	}
	gl.st = 0;
}

void	ft_cd_to_home(t_env **env, char *oldcwd)
{
	t_env	*top;
	int		i;

	top = *env;
	i = 0;
	while (top)
	{
		if (ft_strcmp(top->name, "HOME") == 0)
		{
			if (chdir(top->value) == -1)
				return (perror("chdir"));
			ft_change_pwd_oldpwd(env, oldcwd);
			i++;
		}
		top = top->next;
	}
	if (i == 0)
		ft_putendl_fd("cd: HOME not set", 2);
}

void	ft_change_pwd_oldpwd(t_env **env, char *oldcwd)
{
	char	cwd[1024];
	t_env	*top;

	getcwd(cwd, 1024);
	top = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->name, "PWD") == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(cwd);
		}
		else if (ft_strcmp((*env)->name, "OLDPWD") == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(oldcwd);
		}
		*env = (*env)->next;
	}
	*env = top;
}
