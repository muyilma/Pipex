#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

char *find_path(char **env, char *arg)
{
    int i;
    i = -1;
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

void open_file(int ac, char **av)
{
    int fd_infile;
    int fd_outfile;
    fd_infile = open(av[1], O_RDONLY);
    if (fd_infile < 0)
    {
        perror("Error");
        exit(0);
    }
    dup2(fd_infile, 0);
    fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd_outfile < 0)
    {
        perror("Error");
        exit(0);
    }
    dup2(fd_outfile, 1);
}

int main(int ac, char **av, char **env)
{
    char *directory;
    char **cmd;
    int pid;
    int i;
    int deneme;
    deneme = 0;

    pid = fork();
    open_file(ac, av);
    cmd = ft_split(av[2], ' ');
    directory = find_path(env, cmd[0]);
    if (pid == 0)
    {
        printf("%d\n", pid);
        i = execve(directory, cmd, env);
        if (i == -1)
            write(2, "Hatali komut", 13);
    }
    open_file(ac, av);
    cmd = ft_split(av[3], ' ');
    directory = find_path(env, cmd[0]);
    i = execve(directory, cmd, env);
    if (i == -1)
        write(2, "Hatali komut", 13);

    return 0;
}
