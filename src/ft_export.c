/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:26:24 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/16 13:44:14 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_export(t_lexer *lexer, t_env **env)
{
	t_env	*head0;
	t_env	*head1;
	int		index;
	char	**ptr;

	index = 0;
	ptr = NULL;
	head0 = *env;
	head1 = *env;
	ft_sort_env(env);
	if (!lexer->next)
	{
		while (head1)
		{
			while (head0->index != index)
				head0 = head0->next;
			if (head0->value)
				printf("declare -x %s=\"%s\"\n", head0->key, head0->value);
			else
				printf("declare -x %s\n", head0->key);
			head1 = head1->next;
			head0 = *env;
			index++;
		}
	}
	else if (lexer->next)
	{
		ptr = ft_split_export(lexer->next->content);
		if (ptr == NULL)
			return (ft_putendl_fd("not a valid identifier", 2));//khasni free ptr kamlo
		ft_inject_var(ptr[0], ptr[1], env);
		free(ptr);
		// free(ptr[0]);
		// free(ptr[1]);
	}
}

void	ft_inject_var(char *name, char *value, t_env **env)
{
	t_env	*head;
	int		already_exists;

	head = *env;
	already_exists = 0;
	while (*env)
	{
		if (ft_strcmp((*env)->key, name) == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			already_exists = 1;
		}
		(*env) = (*env)->next;
	}
	*env = head;
	if (already_exists == 0)
	{
		ft_lstadd_back_env(env, ft_lstnew_env(name, value));
	}
}

char	**ft_split_export(char *str)
{
	int	i;
	char	**ptr;

	i = 0;
	ptr = malloc(sizeof(char *) * 2);
	while (str[i] && str[i] != '=')
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (NULL);
		if(ft_if_condition(str[i]) == 1)
			return (NULL);
		i++;
	}
	i = 0;
	ptr[0] = ft_strdup("");
	while (str[i] && str[i] != '=')
		ptr[0] = ft_join(ptr[0], str[i++]);
	if (str[i] != '\0')
	{
		i++;
		ptr[1] = ft_strdup("");
	}
	while (str[i])
	{
		printf("bb\n");
		ptr[1] = ft_join(ptr[1], str[i++]);
	}
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
			if (ft_strcmp(top->key, (*env)->key) > 0)
				i++;
			*env = (*env)->next;
		}
		top->index = i;
		top = top->next;
	}
	*env = tmp;
	top = tmp;
}
