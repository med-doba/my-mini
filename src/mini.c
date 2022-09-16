/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:34:05 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/15 23:50:31 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_sighandler(int sig)
{
	if (sig == 2 && var.id == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		var.st = 1;
	}
	else if (sig == 2 && var.id == 1 && ft_strncmp(var.usr, "./minishell", 11))
	{
		open("/Users/med-doba/.1", O_CREAT);
		printf("\n");
	}
	if (sig == 3 && var.id == 1 && ft_strncmp(var.usr, "./minishell", 11))
	{
		open("/Users/med-doba/.2", O_CREAT);
		printf("Quit: 3\n");
	}
	else if (sig == 3 && var.id == 0)
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
	t_lexer	*top;
	char	*stock;

	stock = NULL;
	while (1)
	{
		lexer = NULL;
		var.id = 0;
		rtn = readline("MiniShell>$");
		var.usr = rtn;
		if (rtn == NULL)
			return (free(rtn), ft_control_d());
		add_history(rtn);
		ft_lexer(&lexer, rtn, &stock);
		top = lexer;
		ft_expand(&lexer, env);
		ft_parser(&lexer);
		ft_collect_cmd(&lexer);
		while(lexer)
		{
			if (ft_strcmp(lexer->content, "env") == 0)
				ft_env(env);
			if (ft_strcmp(lexer->content, "pwd") == 0)
				ft_pwd(env);
			if (ft_strcmp(lexer->content, "cd") == 0)
				ft_cd(lexer, &env);
			if (ft_strcmp(lexer->content, "export") == 0)
				ft_export(lexer, &env);
			if (ft_strcmp(lexer->content, "exit") == 0)
				ft_exit(lexer);
			if (ft_strcmp(lexer->content, "echo") == 0)
				ft_echo(lexer);
			// printf("cmd=%s$\n", lexer->content);
			// printf("ch=%c$\n", lexer->ch);
			// printf("------------------------------\n");
			lexer = lexer->next;
		}
		if (lexer != NULL)
			ft_free_lst(&lexer);
		free(rtn);
	}
}

void	ft_init_global(void)
{
	var.st = 0;
	var.id = 0;
	var.cpid = 0;
	var.usr = NULL;
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
	env = ft_environment(envp, env);
	ft_handle(env);
	ft_free_lst_env(&env);
	return (0);
}
