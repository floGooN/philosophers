/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/01 19:14:06 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#include <unistd.h>


/* ====	PROTOTYPES	==== */

// parsing/parsing.c
int		parsing(int argc, char **argv, int *tab_arg);

// main/utils.c
int		print_error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void  free_lst(t_philo *head_lst);

// init/init.c
t_philo	*socrate_maker(int *tab_args);

/* ====	PROTOTYPES	==== */

/*void	*sleep_and_die(void *tab_arg)
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
	printf("%ld %ld died\n", ((tv[2].tv_usec - tv[0].tv_usec) * 1000 + \
                            (tv[2].tv_sec - tv[0].tv_sec) / 1000), new);
	return (NULL);
}*/

void *eat_routine(void *arg)
{
  t_philo         *lst;

  pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
  lst = (t_philo *) arg;
  printf("thread nb %ld, index = %d from eat\n", lst->philo_id, lst->index);
  pthread_mutex_unlock(&lst->shared_mutex[0]);
  return (NULL);
}

void *sleep_routine(void *arg)
{
  struct timeval	tv[3];
  t_philo         *lst;

  lst = (t_philo *) arg;

  gettimeofday(&tv[0], NULL);
	while (lst->args[2] > 0)
	{
		gettimeofday(&tv[1], NULL);
		usleep(10);
		gettimeofday(&tv[2], NULL);
  	lst->args[2] -= (int)((tv[2].tv_usec - tv[1].tv_usec));
	}
	gettimeofday(&tv[2], NULL);
  pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
	printf("%ld %ld is sleeping -> index %d\n", ((tv[2].tv_usec - tv[0].tv_usec) * 1000 + \
                            (tv[2].tv_sec - tv[0].tv_sec) / 1000), lst->philo_id, lst->index);
  pthread_mutex_unlock(&lst->shared_mutex[0]);
  return (NULL);
}

void *think_routine(void *arg)
{
  t_philo         *lst;

  pthread_mutex_lock(&((t_philo *)arg)->shared_mutex[0]);
  lst = (t_philo *) arg;
  printf("thread nb %ld, index = %d from think\n", lst->philo_id, lst->index);
  pthread_mutex_unlock(&lst->shared_mutex[0]);
  return (NULL);
}

bool  launch_threads(t_philo *lst)
{
  t_philo *head_lst;

  head_lst = lst;
  while (lst)
  {
    if (lst->index % 2 == 0)
    {
      if (pthread_create(&(lst)->philo_id, NULL, sleep_routine, lst))
        return (1);
    }
    else
    {
      if (pthread_create(&(lst)->philo_id, NULL, sleep_routine, lst))
        return (1);
    }
    lst = lst->next;
  }
  return (0);
}

int	main(int argc, char **argv)
{
	int			  tab_arg[5];
	t_philo		*head_lst;

	if (argc != 5 && argc != 6)
		return (print_error("Nb of arguments is invalid\n"), 0);
	if (parsing(argc, argv, tab_arg))
		return (0);
  if (argc == 5)
	{
    head_lst = socrate_maker(tab_arg);
    t_philo *tmp = head_lst;
		if (!head_lst)
        return (0);
    if (launch_threads(head_lst))
        return (free_lst(head_lst), 0);
    while (tmp)
    {
      pthread_join(tmp->philo_id, NULL);
      tmp = tmp->next;
    }
    free_lst(head_lst);
	}
	return (0);
}
	// if (tab_arg[0] == 1)
	// {
	// 	th = (pthread_t *) sleep_and_die(tab_arg);
	// 	if (th)
	// 		return (pthread_join(th, NULL), 0);
  //   else
  //     return (print_error("Crash thread initialisation\n"), 0);
	// }




	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
