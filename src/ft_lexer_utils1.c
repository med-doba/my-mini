/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:08:15 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/16 11:21:58 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_add_node(t_lexer **lexer, char **stock, char ch, int linked)
{
	t_lexer	*node;

	node = ft_lstnew(*stock, linked);
	node->ch = ch;
	ft_lstadd_back(lexer, node);
	free(*stock);
	*stock = NULL;
}

char	*ft_char_to_str(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	ft_string(t_lexer **lexer, char **stock, char *str, int *i)
{
	char	ch;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		ch = str[*i];
		*stock = ft_scan_quotes(str, str[*i], i);
		if (*stock == NULL)
			return (1);
		if (ft_check_case03(str[*i]) == 1)
			ft_add_node(lexer, stock, ch, 1);
		else
			ft_add_node(lexer, stock, ch, 0);
	}
	if (ft_check_case(str[*i]) == 0)
	{
		*stock = ft_strdup("");
		while (ft_check_case(str[*i]) == 0)
			*stock = ft_join(*stock, str[(*i)++]);
		if (ft_check_case03(str[*i]) == 1)
			ft_add_node(lexer, stock, 0, 1);
		else
			ft_add_node(lexer, stock, 0, 0);
	}
	return (0);
}

void	freeall(char **p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}

void	freeall_fd(int **p, int i)
{
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
}
