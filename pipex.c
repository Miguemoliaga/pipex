/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:48:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/17 20:43:35 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *com, char **env)
{
	char	**mat;
	char	*route;
	char	**paths;

	paths = parsepath(env);
	mat = ft_split(com, ' ');
	route = checkpath(mat[0], paths);
	freemat(paths);
	if (execve(route, mat, env) < 0)
		errormsg(3);
}

void	proc_in(int *pipe, char *in_file, char *com, char **env)
{
	int	fd;

	close(pipe[0]);
	fd = open(in_file, O_RDONLY);
	if (fd < 0)
		errormsg(2);
	dup2(fd, 0);
	close(fd);
	dup2(pipe[1], 1);
	close(pipe[1]);
	ft_execute(com, env);
}

void	proc_out(int *pipe, char *out_file, char *com, char **env)
{
	int	fd;

	fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		errormsg(2);
	dup2(pipe[0], 0);
	close(pipe[0]);
	dup2(fd, 1);
	close(pipe[1]);
	ft_execute(com, env);
}

int	main(int argc, char **argv, char **env)
{
	int		arr[2];
	pid_t	proc_id;	

	if (argc != 5)
		errormsg(1);
	pipe(arr);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(3);
	if (!proc_id)
		proc_in(arr, argv[1], argv[2], env);
	waitpid(proc_id, NULL, 0);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(3);
	if (!proc_id)
		proc_out(arr, argv[4], argv[3], env);
	//waitpid(proc_id, NULL, 0);
	return (0);
}
