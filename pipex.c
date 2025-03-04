#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

char *find_path(char **env, char *arg)
{
    int i = -1;
    char **paths;
    char *temp;
    char *directory;

    if (!arg)
        return NULL;

    while (env[++i])
    {
        if (!ft_strncmp(env[i], "PATH", 4))
            break;
    }

    paths = ft_split(env[i] + 5, ':');
    directory = ft_strjoin(paths[3], "/");
    temp = directory;
    directory = ft_strjoin(directory, arg);
    free(temp);
    free_arg(paths);
    return directory;
}

void command_start(char *av, char **env)
{
    char **cmd;
    char *directory;

    if (!av || !av[0])
        ft_error(6);
    cmd = ft_split(av, ' ');
    directory = find_path(env, cmd[0]);
    if (!directory)
        ft_error(7);
    execve(directory, cmd, env);
    perror("Execve failed");
    free_arg(cmd);
    free(directory);
    exit(1);
}

void child(int *fd, int ac, char **av, char **env)
{
    open_file(ac, av, 0);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    command_start(av[2], env);
}

void parent(int *fd, int ac, char **av, char **env)
{
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    open_file(ac, av, 1);
    command_start(av[3], env);
}

int main(int ac, char **av, char **env)
{
    int pid;
    int fd[2];

    if (ac != 5)
        ft_error(1);
    if (pipe(fd) == -1)
        ft_error(2);
    open_file(ac, av, 2);
    pid = fork();
    if (pid == -1)
        ft_error(3);
    else if (pid == 0)
        child(fd, ac, av, env);
    waitpid(pid, NULL, 0);
    parent(fd, ac, av, env);
    return 0;
}
