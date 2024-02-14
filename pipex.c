/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:48:29 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/14 19:56:32 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *com, char **env)
{
	char	**mat;
	char	*route;
	char	**paths;

	paths = parsepath(env);
	printf("com: %s\n", com);
	mat = ft_split(com, ' ');
	printf("prepath: %s\n", mat[0]);
	route = checkpath(mat[0], paths);
	freemat(paths);
	printf("RUTA: %s\n", route);
	execve(route, mat, env);
}

void	proc_in(int *pipe, char *in_file, char *com, char **env)
{
	int	fd;

	close(pipe[0]);
	printf("pasa x aqui\n");
	fd = open(in_file, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	dup2(pipe[1], 1);
	close(pipe[0]);
	ft_execute(com, env);
}

void	proc_out(int *pipe, char *out_file, char *com, char **env)
{
	int	fd;

	fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | O_APPEND);
	/*
	if (fd < 0)
		msg_error("Error in first file");
	*/
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

	if (argc != 5)
	{
		return (0);
		//salida de error por argumentoos invalidos	
	}
	pipe(arr);
	proc_id = fork();
	if (proc_id == -1)
		return (0);
		//salida de error por creacion fallida de primer proceso hijo
	if (!proc_id)
	{
		proc_in(arr, argv[1], argv[2], env);
	}
	proc_id = fork();
	if (proc_id == -1)
		return (0);
		//salida de error por creacion fallida de segundo proceso hijo
	if (!proc_id)
		proc_out(arr, argv[4], argv[3], env);
	return (0);
}
