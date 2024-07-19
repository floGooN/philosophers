/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:00:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/19 17:36:50 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str);

static int	skip_spaces(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

static long	check_overflow(long rslt, const char *nptr, size_t index, int sign)
{
	long	max;

	max = 9223372036854775807;
	if (ft_strlen(nptr) > 11)
		return (-1);
	if (rslt > max / 10 || (rslt == max / 10 && nptr[index] - '0' > 7))
	{
		if (sign == -1)
			return (-2147483649);
		else
			return (2147483648);
	}
	return (1);
}

long	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;
	size_t	i;

	result = 0;
	sign = 1;
	i = skip_spaces(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (check_overflow(result, nptr, i, sign) == -1)
			return (-2147483649);
		else if (!check_overflow(result, nptr, i, sign))
			return (2147483648);
		else
			result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * sign);
}
