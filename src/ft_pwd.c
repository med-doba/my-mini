/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:37:18 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/09 10:57:04 by amasnaou         ###   ########.fr       */
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
