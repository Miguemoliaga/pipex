/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:15:29 by mmartine          #+#    #+#             */
/*   Updated: 2023/08/04 16:28:15 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa_caps(unsigned int num)
{
	int		ret;
	char	*base;

	ret = 0;
	base = "0123456789ABCDEF";
	if (num < 16)
		ret += write(1, &base[num], 1);
	else
	{
		ret += ft_printhexa_caps(num / 16);
		ret += ft_printhexa_caps(num % 16);
	}
	return (ret);
}

int	ft_printhexa_minus(unsigned int num)
{
	int		ret;
	char	*base;

	ret = 0;
	base = "0123456789abcdef";
	if (num < 16)
		ret += write(1, &base[num], 1);
	else
	{
		ret += ft_printhexa_minus(num / 16);
		ret += ft_printhexa_minus(num % 16);
	}
	return (ret);
}

static int	ft_printhexalong(unsigned long num)
{
	int		ret;
	char	*base;

	ret = 0;
	base = "0123456789abcdef";
	if (num < 16)
		ret += write(1, &base[num], 1);
	else
	{
		ret += ft_printhexalong(num / 16);
		ret += ft_printhexalong(num % 16);
	}
	return (ret);
}

int	ft_printpointer(void *pointer)
{
	unsigned long	num;
	int				ret;

	if (!pointer)
		return (write(1, "0x0", 3));
	num = (unsigned long) pointer;
	ret = write(1, "0x", 2);
	ret += ft_printhexalong(num);
	return (ret);
}
