#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void ft_error(int error_code)
{
    if (error_code == 1)
        perror("Usage: infile cmd1 cmd2 outfile");
    else if (error_code == 2)
        perror("Pipe error");
    else if (error_code == 3)
        perror("Fork failed");
    else if (error_code == 4)
        perror("Error opening input file");
    else if (error_code == 5)
        perror("Error opening output file");
    else if (error_code == 6)
        perror("empty command");
    else if (error_code == 6)
        perror("command not found");
    exit(1);
}
void free_arg(char **arg)
{
    int i;
    i = -1;
    while (arg[++i])
        free(arg[i]);
    free(arg);
}

void open_file(int ac, char **av, int chose)
{
    int fd;

    if (chose == 0 || chose == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd < 0)
            ft_error(4);
        dup2(fd, 0);
    }
    else if (chose == 1 || chose == 2)
    {
        fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
            ft_error(5);
        dup2(fd, 1);
    }
    close(fd);
}
