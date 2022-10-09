/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:27:32 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/09 18:21:06 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_echo(t_lexer *lexer)
{
	int	space;
	int	newline;
	int	firstone;

	firstone = 0;
	space = 0;
	newline = 0;
	if (!lexer->next || lexer->next->ch == 'R')
		printf("\n");
	else
	{
		lexer = lexer->next;
		while (lexer && lexer->ch != '|')
		{
			while(lexer && lexer->ch != '|' && lexer->ch == 'R')
				lexer = lexer->next->next;
			if (!lexer || lexer->ch == '|')
				break ;
			if (firstone == 0)
				while (lexer && ft_check_option_echo(lexer->content, &newline) == 2)
					lexer = lexer->next;
			firstone = 1;
			if (space == 1)
				printf(" ");
			printf ("%s", lexer->content);
			space = 1;
			lexer = lexer->next;
		}
	}
	if (space == 1 && newline == 0)
		printf("\n");
	gl.st = 0;
}

int	ft_check_option_echo(char *str, int *newline)
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
