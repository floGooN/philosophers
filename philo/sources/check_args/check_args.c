/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:46:59 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/25 15:40:41 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	ft_isdigit(char *arg)
{
	size_t	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '-' || arg[i] == '+')
	{
		i++;
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
	}
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv, int *tab_arg)
{
	int			i_argv;
	int			i_tab_arg;
	long int	tmp;

	i_argv = 1;
	i_tab_arg = 0;
	while (i_argv < argc)
	{
		if (ft_isdigit(argv[i_argv]))
			return (ft_perror("Error -> Arguments must be numbers\n"));
		tmp = ft_atoi(argv[i_argv]);
		if (tmp <= 0 || tmp > INT_MAX)
			return (ft_perror("Error -> an argument is invalid\n"));
		tab_arg[i_tab_arg] = (int)tmp;
		i_argv++;
		i_tab_arg++;
	}
	return (0);
}
