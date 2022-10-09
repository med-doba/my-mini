/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:34:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/09 18:17:54 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_sighandler(int sig)
{
	if (sig == 2 && gl.sig == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		gl.st = 1;
	}
	else if (sig == 2 && gl.sig == 1 && ft_strncmp(gl.rl_r, "./minishell", 11))
	{
		open("/Users/med-doba/.1", O_CREAT);
		printf("\n");
	}
	if (sig == 3 && gl.sig == 1 && ft_strncmp(gl.rl_r, "./minishell", 11))
	{
		open("/Users/med-doba/.2", O_CREAT);
		printf("Quit: 3\n");
	}
	else if (sig == 3 && gl.sig == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_control_d(void)
{
	printf("\033[11C\033[1A exit\n");
	exit(0);
}

void	ft_handle(t_env *env)
{
	char	*rtn;
	t_lexer	*lexer;
	char	*stock;

	stock = NULL;
	while (1)
	{
		lexer = NULL;
		gl.sig = 0;
		rtn = readline("MiniShell>$");
		rtn = ft_strtrim(rtn, " \t");
		gl.rl_r = rtn;
		if (rtn == NULL)
			return (free(rtn), ft_control_d());
		add_history(rtn);
		ft_lexer(&lexer, rtn, &stock);
		ft_expand(&lexer, env);
		ft_parser(&lexer);;
		if (rtn[0] != '\0')
			ft_execution(&lexer, &env);
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
	}
}

void	ft_init_global(void)
{
	gl.st = 0;
	gl.sig = 0;
	gl.her_doc = 0;
	gl.rl_r = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	ft_header();
	(void)ac;
	(void)av;
	ft_init_global();
	signal(2, ft_sighandler);
	signal(3, SIG_IGN);
	signal(3, ft_sighandler);
	gl.arg_env = envp;
	env = ft_environment(envp, env);
	ft_handle(env);
	ft_free_lst_env(&env);
	return (0);
}
