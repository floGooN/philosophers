/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/04/29 10:30:13 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

#include <unistd.h>

/* ====	PROTOTYPES	==== */
int		parsing(int argc, char **argv, int *tab_arg);
int		print_error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
/* ====	PROTOTYPES	==== */

void	*sleep_and_die(void *tab_arg)
{
	static pthread_t	new;
	struct timeval		tv[3];
	int					tmp;

	if (!new)
	{
		if (pthread_create(&new, NULL, sleep_and_die, tab_arg))
			return (NULL);
		return (&new);
	}
	write(1, "One fork for eating spaghetti!!\nShame on you, ", 46);
	write(1, "I prefer dying than eating !!\n", 31);
	gettimeofday(&tv[0], NULL);
	while (((int *)tab_arg)[1] > 0)
	{
		gettimeofday(&tv[1], NULL);
		usleep(30);
		gettimeofday(&tv[2], NULL);
  	((int *)tab_arg)[1] -= (int)((tv[2].tv_usec - tv[1].tv_usec));
	}
	gettimeofday(&tv[2], NULL);
	printf("%ld %ld died\n", ((tv[2].tv_usec - tv[0].tv_usec) * 1000 + ((tv[2].tv_sec - tv[0].tv_sec) / 1000)), new);
	return (NULL);
}

typedef struct s_philo
{
	pthread_t		philo_id;
	pthread_t		*philo_head;
	int				*args;
	struct s_philo	*next;
}	t_philo ;

int	join_thread(t_philo *lst)
{
	t_philo	*head;

	head = lst;
	while (lst)
	{
		if (pthread_join(lst->philo_id, NULL))
			return (1);
		lst = lst->next;
	}
}


void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	printf("%ld arrive\n", philo->philo_id);
	return (NULL);
}

t_philo	*socrate_maker(int *tab_args)
{
	t_philo	*lst;
	t_philo	*head;
	int		tmp;

	tmp = tab_args[0];
	lst = ft_calloc(1, sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->args = tab_args;
	if (pthread_create(&lst->philo_id, NULL, start_routine, tab_args))
		return (NULL);
	lst->philo_head = &lst->philo_id;
	lst->next = NULL;
	head = lst;
	while (--tmp)
	{
		lst->next = ft_calloc(1, sizeof(t_philo));
		if (!lst->next)
			return (/*free head*/NULL);
		if (pthread_create(&lst->next->philo_id, NULL, start_routine, tab_args))
			return (/*free lst*/NULL);
		lst->next->philo_head = &head->philo_id;
		lst = lst->next;
	}
	return (lst);
}

int	main(int argc, char **argv)
{
	int			tab_arg[5];
	t_philo		*head_lst;
	pthread_t	**th;

	if (argc != 5 && argc != 6)
		return (print_error("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
	if (tab_arg[0] == 1)
	{
		*th = (pthread_t *) sleep_and_die(tab_arg);
		if (*th)
			pthread_join(**th, NULL);
    	else
    		return (print_error("Crash thread initialisation\n"), 0);
	}



	else if (argc == 5)
	{
		*th = socrate_maker(tab_arg[0]);
		if (!*th)
    	  return (print_error("Crash thread initialisation\n"), 0);
		if (join_thread(*th))
			return (print_error("Error -> join\n"), 0);
		while(tab_arg[0]--)
		{
			free(*th);
		}
	}
	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
	return (0);
}
