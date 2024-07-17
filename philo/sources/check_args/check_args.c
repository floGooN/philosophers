/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:46:59 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 11:09:38 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool ft_isdigit(char *arg)
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
	size_t		i_argv;
	short		  i_tab_arg;
	long int	tmp;

	i_argv = 1;
	i_tab_arg = 0;
	while (i_argv < argc)
	{
		if (ft_isdigit(argv[i_argv]))
			return (ft_perror("Error -> Arguments must be numbers\n"));
		tmp = ft_atoi(argv[i_argv]);
		if (i_tab_arg == 4)
		{
			if (tmp < 0 || tmp > INT_MAX)
				return (ft_perror("Error -> last arg invalid\n"));
		}
		else
			if (tmp < 0 || tmp > INT_MAX)
				return (ft_perror("Error -> an argument is invalid\n"));
		tab_arg[i_tab_arg] = (int) tmp;
		i_argv++;
		i_tab_arg++;
	}
	return (0);
}
