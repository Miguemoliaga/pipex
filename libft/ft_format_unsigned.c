/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:26:35 by mmartine          #+#    #+#             */
/*   Updated: 2023/08/04 16:28:25 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunsigned(unsigned int number)
{
	int	ret;

	ret = 0;
	if (number < 10)
		ret += ft_printchar(number + '0');
	else
	{
		ret += ft_printnum(number / 10);
		ret += ft_printnum(number % 10);
	}
	return (ret);
}
