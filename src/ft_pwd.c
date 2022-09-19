/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:37:18 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/19 16:37:57 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_pwd(t_env *env)
{
	t_env	*top;
	char	pwd[1024];

	top = env;
	// while (top)
	// {
	// 	if (ft_strcmp(top->key, "PWD") == 0)
	// 	{
	// 		printf("%s\n", top->value);
	// 		break ;
	// 	}
	// 	top = top->next;
	// }
	if (getcwd(pwd, 1024) == NULL)
		return (perror("getcwd"));
	printf("%s\n", pwd);
}
