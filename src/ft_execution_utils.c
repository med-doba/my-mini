/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:00:22 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/08 15:09:07 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**ft_get_full_cmd(t_lexer *lexer)
{
	char	*ptr;
	char	**two;
	t_lexer *tmp;

	tmp = lexer;
	ptr = ft_strdup("");
	while (tmp && tmp->ch != '|')
	{
		if (tmp != NULL && tmp->ch == 'R')
			tmp = tmp->next->next;
		if (tmp != NULL && tmp->ch != 'R' && tmp->ch != '|')
		{
			ptr = ft_strjoin(ptr, ft_strjoin(tmp->content, ";"));
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->ch != 'R' && tmp->ch != '|')
		{
			ptr = ft_strjoin(ptr, ft_strjoin(tmp->content, ";"));
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->ch != '|')
		{
			if (tmp && ft_strcmp(tmp->content, "<<") == 0)
			{
				ptr = ft_strjoin(ptr, ".her_doc");
				tmp = tmp->next->next;
			}
		}
	}
	two = ft_split(ptr, ';');
	return (free(ptr), two);
}

char	*ft_find_path(char *cmd, t_env *env)
{
	char	*path;
	t_env	*top;
	char	**ptr;

	ptr = NULL;
	path = NULL;
	top = env;
	if (ft_strncmp(cmd, "./", 2) && ft_strncmp(cmd, "/", 1))
	{
		while (top)
		{
			if (ft_strcmp(top->name, "PATH") == 0)
			{
				ptr = ft_split(top->value, ':');
				if ((path = ft_collect_path(cmd, ptr)))
					return (path);
				return (ft_free_2d(ptr), NULL);
			}
			top = top->next;
		}
	}
	cmd = ft_strdup(cmd);
	return (cmd);
}

char	*ft_collect_path(char	*cmd, char **ptr)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
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
	return (0);
}
