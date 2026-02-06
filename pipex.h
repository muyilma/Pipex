/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musyilma <musyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:27:21 by musyilma          #+#    #+#             */
/*   Updated: 2025/03/05 09:48:52 by musyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	free_arg(char **arg);
void	open_file(int ac, char **av, int chose);
void	ft_error(int chose);
void	arg_check(char *av, char **env);
char	*find_path(char **env, char *arg);

#endif