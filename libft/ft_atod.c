/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg <carlosg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:30:10 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/30 23:33:33 by carlosg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_spaces_and_sign(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}

static void	reading_digits(const char **str, double *nbr)
{
	while (**str >= '0' && **str <= '9')
	{
		*nbr = (*nbr * 10) + (**str - '0');
		(*str)++;
	}
}

double	ft_atod(const char *str)
{
	double	nbr;
	int		sign;
	double	dec;
	int		digits;

	nbr = 0;
	sign = 1;
	dec = 0;
	digits = 0;
	skip_spaces_and_sign(&str, &sign);
	reading_digits(&str, &nbr);
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			dec = (dec * 10) + (*str - '0');
			digits++;
			str++;
		}
	}
	while (digits--)
		dec /= 10;
	return ((nbr + dec) * sign);
}
