/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:16:09 by mmartine          #+#    #+#             */
/*   Updated: 2023/07/26 21:16:26 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	getdecimal(char *str, double result)
{
	double	divider;
	double	fraction;

	fraction = 0.0;
	divider = 10.0;
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction + (*str++ - '0') / divider;
			divider *= 10.0;
		}
		result += fraction;
	}
	return (result);
}

double	ft_strtod(const char *str)
{
	int		sign;
	double	result;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	result = 0.0;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	return (getdecimal((char *)str, result) * sign);
}
