/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:47:56 by mmartine          #+#    #+#             */
/*   Updated: 2024/02/21 16:42:10 by mmartine         ###   ########.fr       */
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
char	*checkpath(char *order, char **paths);
void	errormsg(int code);

#endif