#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

char *find_path(char **env, char *arg)
{
    int i;
    i = -1;
    if (!arg)
        return NULL;

    while (env[++i])
    {
        if (!ft_strncmp(env[i], "PATH", 4))
            break;
    }
    env = ft_split(env[i] + 5, ':');
    env[3] = ft_strjoin(env[3], "/");
    env[3] = ft_strjoin(env[3], arg);

    return env[3];
}

void open_file(int ac, char **av, int ana)
{
    int fd_infile;
    int fd_outfile;

    if (ana == 0)
    {
        fd_infile = open(av[1], O_RDONLY);
        if (fd_infile < 0)
        {
            perror("Error");
            exit(0);
        }
        dup2(fd_infile, 0);
    }
    else if (ana == 1)
    {
        fd_outfile = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd_outfile < 0)
        {
            perror("Error");
            exit(0);
        }
        dup2(fd_outfile, 1);
    }
}

void command_start(char *av, char **env)
{
    char **cmd;
    char *directory;
    int i;

    cmd = ft_split(av, ' ');
    directory = find_path(env, cmd[0]);
    i = execve(directory, cmd, env);
    if (i == -1)
    {
        write(2, "Hatali komut", 13); 
        exit(127);
    }
}

int main(int ac, char **av, char **env)
{
    char *directory;
    char **cmd;
    int i;
    int pid;
    int fd[2];

    if (pipe(fd) == -1)
        exit(1);

    pid = fork();
    if (pid == 0)
    {
        printf("-%d-\n",pid);
        pid = fork();
        
        printf("-%d-\n",pid);
        open_file(ac, av,0);
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        command_start(av[2], env);
    }
    waitpid(pid, NULL, 0);
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    open_file(ac, av,1);
    command_start(av[3], env);
    return 0;
}