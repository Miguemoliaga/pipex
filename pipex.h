/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:47:56 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/23 17:34:40 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"
# include <fcntl.h>

char	**parsepath(char **mat);
void	freemat(char **mat);
char	*checkpath(char *order, char **paths, char *file);
void	errormsg(int code, char *file);

#endif