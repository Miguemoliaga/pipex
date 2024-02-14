/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:09:58 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/14 19:52:22 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freemat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
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
	if (access(order, X_OK))
		return (order);
	while (paths[i])
	{
		slash = ft_strjoin(paths[i], "/");
		route = ft_strjoin(slash, order);
		free(slash);
		printf("%s\n", route);
		if (!access(route, X_OK))
		{
			//liberar route tras la salida.
			return (route);
		}
		free(route);
		i++;
	}
	//flag para marcar que no se ha encontrado ruta posible 
	return (0);
}