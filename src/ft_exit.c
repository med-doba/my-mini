/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:02:10 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/14 12:58:38 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_exit(t_lexer *lexer)
{
	if (!lexer->next)
		exit(0);//khasha tkon b akhir exit status
	else if (lexer->next)
	{
		if(ft_test_arg_exit(lexer->next->content, lexer->next->ch) == 0)
			exit(ft_atoi(lexer->next->content));
		else
			ft_putendl_fd("Error: numeric argument required" ,2);
	}
	else if (lexer->next->next)
	{
		if(ft_test_arg_exit(lexer->next->next->content, lexer->next->next->ch) != 2)
			ft_putendl_fd("Error: exit too many arguments", 2);
	}
}

int	ft_test_arg_exit(char	*str, char ch)
{
	int	i;
	long long	nbr;

	i = 0;
	nbr = ft_atoi(str);
	if ((str[i] == '|' || str[i] == '<' ||str[i] == '>') && ch != '"' && ch != '\'')
		return (2);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			return (1);
		i++;
	}
	if (nbr > 9223372036854775807 || nbr < -9223372036854775807)
		return (1);
	return (0);
}
