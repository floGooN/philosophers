/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 23:02:56 by florian          ###   ########.fr       */
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
void  free_philo(t_philo *philo_tab, size_t tab_size);

// init/init.c
t_philo	*socrate_maker(int *tab_args, bool *ready_ptr);

// main/philo.c
void  *routine_a(void *arg);
void  *routine_b(void *arg);

/* ====	PROTOTYPES	==== */

bool  launch_philo(t_philo *lst)
{
  while (lst)
  {
    if (lst->index % 2)
    {
      if (pthread_create(&(lst)->philo_id, NULL, routine_a, lst))
        return (1);
    }
    else
    {
      if (pthread_create(&(lst)->philo_id, NULL, routine_b, lst))
        return (1);
    }
    lst = lst->next;
  }
  return (0);
}



int	main(int argc, char **argv)
{
  int		  tab_arg[5];
  t_philo *philo_tab;
  bool    ready;

  if (argc != 5 && argc != 6)
    return (printf("Nb of arguments is invalid\n"), 0);
  if (parsing(argc, argv, tab_arg))
    return (0);
  if (argc == 5)
  {
    philo_tab = socrate_maker(tab_arg, &ready);
    if (!philo_tab)
        return (0);
    if (launch_philo(philo_tab))
        return (free_philo(philo_tab, tab_arg[0]), 0);

    sleep(1);
    free_philo(philo_tab, tab_arg[0]);
  }
  return (0);
}
	/*
	if (tab_arg[1] < tab_arg[2] || tab_arg[1] < tab_arg[3])
		// incoherent argument
	else
		// eat %d time and die
	*/
