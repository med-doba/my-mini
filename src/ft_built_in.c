/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:50:00 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/14 14:34:04 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_built_in(t_lexer *lexer, t_env **env)
{
	if (ft_built_in_lowercase(lexer, env) == -1)
		return (-1);
	return (0);
}

int	ft_built_in_lowercase(t_lexer *lexer, t_env **env)
{
	if (ft_strcmp(lexer->content, "env") == 0)
		return (ft_env(*env), 0);
	else if (ft_strcmp(lexer->content, "pwd") == 0)
		return (ft_pwd(*env), 0);
	else if (ft_strcmp(lexer->content, "cd") == 0)
		return (ft_cd(lexer, env), 0);
	else if (ft_strcmp(lexer->content, "export") == 0)
		return (ft_export(lexer, env), 0);
	else if (ft_strcmp(lexer->content, "unset") == 0)
		return (ft_unset(lexer, env), 0);
	else if (ft_strcmp(lexer->content, "exit") == 0)
		return (ft_exit(lexer), 0);
	else if (ft_strcmp(lexer->content, "echo") == 0)
		return (ft_echo(lexer), 0);
	return (-1);
}
