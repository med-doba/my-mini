/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:37:18 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 18:15:46 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_pwd(t_env *env)
{
	t_env	*top;
	char	pwd[1024];

	top = env;
	while (top)
	{
		if (ft_strcmp(top->name, "PWD") == 0)
		{
			printf("%s\n", top->value);
			return ;
		}
		top = top->next;
	}
	if (getcwd(pwd, 1024) == NULL)
		return (gl.st = 1, perror("getcwd"));
	printf("%s\n", pwd);
	gl.st = 0;
}
