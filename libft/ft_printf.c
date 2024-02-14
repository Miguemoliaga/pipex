/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:45:57 by mmartine          #+#    #+#             */
/*   Updated: 2023/08/04 16:28:56 by mmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_selection(va_list args, char format)
{
	int	n;

	n = 0;
	if (format == '%')
		n = write(1, "%", 1);
	else if (format == 'c')
		n += ft_printchar(va_arg(args, int));
	else if (format == 's')
		n += ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		n += ft_printnum(va_arg(args, int));
	else if (format == 'x')
		n += ft_printhexa_minus(va_arg(args, unsigned int));
	else if (format == 'X')
		n += ft_printhexa_caps(va_arg(args, unsigned int));
	else if (format == 'u')
		n += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == 'p')
		n += ft_printpointer(va_arg(args, void *));
	return (n);
}

int	ft_printf(char const *input, ...)
{
	int		nprint;
	va_list	args;
	int		i;

	nprint = 0;
	i = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			nprint += format_selection(args, input[i + 1]);
			i++;
		}
		else
			nprint += write(1, &input[i], 1);
		i++;
	}
	return (nprint);
}
