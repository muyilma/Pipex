/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musyilma <musyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:26:25 by musyilma          #+#    #+#             */
/*   Updated: 2025/03/05 10:57:39 by musyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_error(int error_code)
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
		perror("Empty command");
	else if (error_code == 6)
		perror("Command not found");
	else if (error_code == 7)
		perror("Command not found");
	exit(1);
}

void	free_arg(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

void	open_file(int ac, char **av, int chose)
{
	int	fd;

	if (chose == 1 || chose == 2)
	{
		fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 2)
			ft_error(5);
		dup2(fd, 1);
	}
	else if (chose == 0 || chose == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 2)
			ft_error(4);
		dup2(fd, 0);
	}
}

void	arg_check(char *av, char **env)
{
	char	**cmd;
	char	*directory;

	if (!av || !av[0])
		ft_error(6);
	cmd = ft_split(av, ' ');
	directory = find_path(env, cmd[0]);
	if (!directory)
		ft_error(7);
	if (access(directory, X_OK) == -1)
	{
		free_arg(cmd);
		free(directory);
		ft_error(7);
	}
	free_arg(cmd);
	free(directory);
}
