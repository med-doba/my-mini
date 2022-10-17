/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:26:24 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/17 16:39:35 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_export_cmd(t_env *env)
{
	t_env	*head0;
	t_env	*head1;
	int		index;

	head0 = env;
	head1 = env;
	index = 0;
	while (head1)
	{
		while (head0->index != index)
			head0 = head0->next;
		if (head0->value)
			printf("declare -x %s=\"%s\"\n", head0->name, head0->value);
		else
			printf("declare -x %s\n", head0->name);
		head1 = head1->next;
		head0 = env;
		index++;
	}
}

void	ft_export(t_lexer *lexer, t_env **env)
{
	char	**ptr;
	int		already_exists;

	already_exists = 0;
	ptr = NULL;
	ft_sort_env(env);
	if (!lexer->next || lexer->next->ch == '|')
		ft_export_cmd(*env);
	lexer = lexer->next;
	while (lexer && lexer->ch != '|' && lexer->ch != 'R')
	{
		ptr = ft_split_export(lexer->content);
		if (ptr == NULL)
			return (gl.st = 1, ft_putendl_fd("not a valid identifier", 2));
		if (ptr[0][0] == '\0')
			return (gl.st = 1, ft_putendl_fd("not a valid identifier", 2),
				ft_free_2d(ptr));
		ft_inject_var(ptr, env, lexer->content, already_exists);
		ft_free_2d(ptr);
		lexer = lexer->next;
	}
	gl.st = 0;
}

void	ft_inject_var(char **ptr, t_env **env, char *str, int already_exists)
{
	t_env	*head;
	t_env	*node;

	head = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->name, ptr[0]) == 0)
		{
			if (!ft_find_char(str, '='))
			{
				free((*env)->value);
				(*env)->value = ft_strdup(ptr[1]);
			}
			already_exists = 1;
		}
		(*env) = (*env)->next;
	}
	*env = head;
	if (already_exists == 0)
	{
		node = ft_lstnew_env(ptr[0], ptr[1]);
		if (node)
			ft_lstadd_back_env(env, node);
	}
}

char	**ft_split_export(char *str)
{
	int		i;
	char	**ptr;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (NULL);
		if (ft_if_condition(str[i]) == 1)
			return (NULL);
		i++;
	}
	i = 0;
	ptr = (char **)malloc(sizeof(char *) * 3);
	ptr[2] = NULL;
	ptr[0] = ft_strdup("");
	while (str[i] && str[i] != '=')
		ptr[0] = ft_join(ptr[0], str[i++]);
	ptr[1] = ft_strdup("");
	if (str[i] != '\0')
		i++;
	while (str[i])
		ptr[1] = ft_join(ptr[1], str[i++]);
	return (ptr);
}

void	ft_sort_env(t_env **env)
{
	t_env	*top;
	t_env	*tmp;
	int		i;

	tmp = *env;
	top = *env;
	while (top)
	{
		i = 0;
		*env = tmp;
		while (*env)
		{
			if (ft_strcmp(top->name, (*env)->name) > 0)
				i++;
			*env = (*env)->next;
		}
		top->index = i;
		top = top->next;
	}
	*env = tmp;
	top = tmp;
}
