/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:27:32 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/15 22:16:36 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_echo(t_lexer *lexer, int space, int newline, int firstone)
{
	if (!lexer || lexer->ch == 'R')
		printf("\n");
	else
	{
		while (lexer && lexer->ch != '|')
		{
			while (lexer && lexer->ch != '|' && lexer->ch == 'R')
				lexer = lexer->next->next;
			if (!lexer || lexer->ch == '|')
				break ;
			if (firstone == 0)
				while (lexer && ft_option_echo(lexer->content, &newline) == 2)
					lexer = lexer->next;
			firstone = 1;
			if (space == 1)
				printf(" ");
			if (lexer)
				printf ("%s", lexer->content);
			space = 1;
			if (lexer)
				lexer = lexer->next;
		}
	}
	if (space == 1 && newline == 0)
		printf("\n");
}

int	ft_option_echo(char *str, int *newline)
{
	char	**ptr;
	int		i;
	int		j;

	ptr = NULL;
	i = 0;
	j = 0;
	if (str && ft_strncmp(str, "-n", 2) == 0)
	{
		ptr = ft_split(str, '-');
		while (ptr[i])
		{
			while (ptr[i][j] && ptr[i][j] == 'n')
				j++;
			if (ptr[i][j] != '\0')
				return (ft_free_2d(ptr), 1);
			i++;
		}
		if (i > 1)
			return (ft_free_2d(ptr), 1);
		*newline = 1;
		return (ft_free_2d(ptr), 2);
	}
	return (0);
}
