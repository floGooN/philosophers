/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/04/28 13:12:30 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

/* ====	PROTOTYPES	==== */
int	parsing(int argc, char **argv, int *tab_arg);
/* ====	PROTOTYPES	==== */

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i++])
		;
	return (i);
}

int	print_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

void	*sleep_and_die(void *tab_arg)
{
	static pthread_t	new;
	struct timeval		tv;
	struct timeval		tmp;

	if (!new)
	{
		if (pthread_create(&new, NULL, sleep_and_die, tab_arg))
			return (NULL);
		return (&new);
	}
	write(1, "One fork for eating spaghetti!!\nShame on you, ", 46);
	write(1, "I prefer dying than eating !!\n", 31);
	while (((int *)tab_arg)[1] > 0)
	{
		gettimeofday(&tv, NULL);
		usleep(30);
		gettimeofday(&tmp, NULL);
		((int *)tab_arg)[1] -= (int)(tmp.tv_usec - tv.tv_usec);
	}
	printf("%ld %ld died\n", ((tmp.tv_usec - tv.tv_usec)), new);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	tab_arg[5];
	pthread_t	*th;

	if (argc != 5 && argc != 6)
		return (print_error("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
	if (tab_arg[0] == 1)
	{
		th = sleep_and_die(tab_arg);
		if (th)
			pthread_join(*th, NULL);
	}
	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	if (argc == 5)
		// eternals philo
	else
		// eat %d time and die
	*/
	return (0);
}