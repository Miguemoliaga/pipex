/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:48:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/28 14:05:56 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	showleaks(void)
{
	system("leaks -q pipex");
}

void	ft_execute(char *com, char **env)
{
	char	**mat;
	char	*route;
	char	**paths;

	paths = parsepath(env);
	mat = ft_split(com, ' ');
	route = checkpath(mat[0], paths);
	freemat(paths);
	execve(route, mat, env);
	freemat(mat);
	free(route);
}

void	proc_in(int *pipe, char *infile, char *com, char **env)
{
	int	fd;

	close(pipe[0]);
	if (access(infile, F_OK))
		errormsg(2);
	fd = open(infile, O_RDONLY);
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
	int	file;

	file = 0;
	if (access(out_file, F_OK))
		file = 1;
	close(pipe[1]);
	fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		errormsg(2);
	dup2(pipe[0], 0);
	close(pipe[0]);
	dup2(fd, 1);
	close(fd);
	ft_execute(com, env);
}

int	main(int argc, char **argv, char **env)
{
	int		arr[2];
	pid_t	proc_id;	
	int		status;

	if (argc != 5)
		errormsg(1);
	pipe(arr);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(4);
	if (!proc_id)
		proc_in(arr, argv[1], argv[2], env);
	if (waitpid(proc_id, &status, WNOHANG) == -1)
		errormsg(5);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		return (-1);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(4);
	if (!proc_id)
		proc_out(arr, argv[4], argv[3], env);
	if (waitpid(proc_id, &status, WNOHANG) == -1)
		errormsg(5);
	close(arr[0]);
	return (0);
}
