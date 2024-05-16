/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/16 09:16:32 by fberthou         ###   ########.fr       */
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
void  free_all(t_philo *philo_tab, int tab_size);

// init/init.c
t_philo	*socrate_maker(int (*tab_args)[5], bool *ready_ptr, bool *is_dead, \
                                        pthread_mutex_t *ready_isdead_mutex);

// main/philo.c
void  *odd_routine(void *arg);
void  *even_routine(void *arg);

/* ====	PROTOTYPES	==== */

bool  launcher(t_philo *philo_tab, int tab_size)
{
  int  i;

  i = 0;
  while (i < tab_size)
  {
    if (philo_tab[i].index % 2)
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, odd_routine, &philo_tab[i]))
        return (1);
    }
    else
    {
      if (pthread_create(&philo_tab[i].philo_id, NULL, even_routine, &philo_tab[i]))
        return (1);
    }
    i++;
  }
  return (0);
}

int	main(int argc, char **argv)
{
  int		          tab_arg[5];
  t_philo         *philo_tab;
  pthread_mutex_t ready_isdead_mutex[2];
  bool            is_dead;
  bool            ready;

  if (argc != 5 && argc != 6)
    return (print_error("Nb of arguments is invalid\n"), 0);
  if (parsing(argc, argv, tab_arg)) // init last arg
    return (0);

  // INIT MAIN THREAD FUNCTION
  ready = 0;
  is_dead = 0;
  pthread_mutex_init(&ready_isdead_mutex[0], NULL);
  pthread_mutex_init(&ready_isdead_mutex[1], NULL);
  // INIT MAIN THREAD FUNCTION

  if (argc == 5)
  {
    philo_tab = socrate_maker(&tab_arg, &ready, &is_dead, ready_isdead_mutex);
    if (!philo_tab)
        return (0);
    if (launcher(philo_tab, tab_arg[0]))
        return (free_all(philo_tab, tab_arg[0]), 0);


  // MAIN THREAD ROUTINE FUNCTION
    pthread_mutex_lock(&ready_isdead_mutex[0]);
    ready = 1;
    pthread_mutex_unlock(&ready_isdead_mutex[0]); 
    while (1)
    {
      pthread_mutex_lock(&ready_isdead_mutex[1]);
      if (is_dead)
      {
        pthread_mutex_unlock(&ready_isdead_mutex[1]);
        break;
      }
      pthread_mutex_unlock(&ready_isdead_mutex[1]);
    }
  // MAIN THREAD ROUTINE FUNCTION



    usleep(5000);
    free_all(philo_tab, tab_arg[0]);
  }
  return (0);
}
