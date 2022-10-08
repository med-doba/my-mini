#include "../mini.h"

void close_pipe(int fd[][2], int n)
{
    int i;

    i = 0;
    while(i < n)
    {
        close(fd[i][1]);
        close(fd[i][0]);
        i++;
    }
}

void	wait_childs(int len, int pid)
{
	int	i;

	i = 0;
	while (i < len)
	{
		wait(NULL);
		i++;
	}
    gl.st = WEXITSTATUS(pid);
}

void open_pipes(int fd[][2], int n)
{
    int i;

    i = 0;
    while(i < n)
    {
        if (pipe(fd[i]) == -1)
            return ;
        i++;
    }
}
void	ft_execute_pipe(t_lexer **lexer, t_env **env, int n)
{
    // pid_t pid;
    int pid;
    int fd[n][2];
    int i;
    int in;
    int out;

    open_pipes(fd, n);
    i = 0;
    out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
    while(*lexer)
    {
        gl.sig = 1;
        pid = fork();
        if (pid == -1)
            return (perror("fork pipe"));
        if (pid == 0)
        {
            if (i < n)
                dup2(fd[i][1],1);
            if (i != 0)
                dup2(fd[i-1][0], 0);
            close_pipe(fd, n);
            if (ft_execution_up(lexer, env) == -1)
                return (exit(1));
            exit(0);
        }
        while (*lexer && (*lexer)->ch != '|')
            *lexer = (*lexer)->next;
        if (*lexer)
            *lexer = (*lexer)->next;
        i++;
    }
    close_pipe(fd, n);
    dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
    wait_childs((n + 1),pid);
}
