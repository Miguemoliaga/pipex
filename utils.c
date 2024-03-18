/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:09:58 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/23 18:05:16 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errormsg(int code)
{
	if (code == 1)
		perror("Numero de argumentos invalido");
	else if (code == 2)
		perror("Error al leer archivo .txt");
	else if (code == 127)
		perror("Ruta/comando inválido");
	else if (code == 4)
		perror("Error al crear un proceso hijo");
	else if (code == 5)
		perror("TIMEOUT");
	exit (1);
}

void	freemat(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

char	**parsepath(char **mat)
{
	int		i;

	i = 0;
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], "PATH", 4))
			return (ft_split(mat[i] + 5, ':'));
		i++;
	}
	return (0);
}

char	*checkpath(char *order, char **paths)
{
	int		i;
	char	*slash;
	char	*route;

	i = 0;
	if (!access(order, X_OK))
		return (order);
	while (paths && paths[i])
	{
		slash = ft_strjoin(paths[i], "/");
		route = ft_strjoin(slash, order);
		free(slash);
		if (!access(route, X_OK))
			return (route);
		free(route);
		i++;
	}
	errormsg(127);
	return (0);
}
