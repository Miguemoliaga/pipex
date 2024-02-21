/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:48:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/21 17:32:58 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	showleaks(void)
{
	system("leaks -q pipex");
}

void	ft_execute(char *com, char **env, char *file)
{
	char	**mat;
	char	*route;
	char	**paths;

	paths = parsepath(env);
	mat = ft_split(com, ' ');
	route = checkpath(mat[0], paths, file);
	freemat(paths);
	execve(route, mat, env);
	freemat(mat);
	free(route);
}

void	proc_in(int *pipe, char *in_file, char *com, char **env)
{
	int	fd;

	close(pipe[0]);
	if (access(in_file, F_OK))
		errormsg(2, NULL);
	fd = open(in_file, O_RDONLY);
	if (fd < 0)
		errormsg(2, NULL);
	dup2(fd, 0);
	close(fd);
	dup2(pipe[1], 1);
	close(pipe[1]);
	ft_execute(com, env, NULL);
}

void	proc_out(int *pipe, char *out_file, char *com, char **env)
{
	int	fd;

	close(pipe[1]);
	fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		errormsg(2, NULL);
	dup2(pipe[0], 0);
	close(pipe[0]);
	dup2(fd, 1);
	close(fd);
	ft_execute(com, env, out_file);
}

int	main(int argc, char **argv, char **env)
{
	int		arr[2];
	pid_t	proc_id;	
	int		status;

	if (argc != 5)
		errormsg(1, NULL);
	pipe(arr);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(4, NULL);
	if (!proc_id)
		proc_in(arr, argv[1], argv[2], env);
	if (waitpid(proc_id, &status, WNOHANG) == -1)
		errormsg(5, NULL);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		return (-1);
	proc_id = fork();
	if (proc_id == -1)
		errormsg(4, NULL);
	if (!proc_id)
		proc_out(arr, argv[4], argv[3], env);
	if (waitpid(proc_id, &status, WNOHANG) == -1)
		errormsg(5, NULL);
	close(arr[0]);
	return (0);
}
