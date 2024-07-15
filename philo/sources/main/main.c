/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/09 17:48:00 by florian          ###   ########.fr       */
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
int		check_args(int argc, char **argv, int *tab_arg);

// main/utils.c
int		print_error(char *str);
void  free_all(t_philo *philo_tab, int tab_size);

// init/init.c
t_philo	*socrate_maker(t_main_th *th_master);

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
    if (philo_tab[i].index % 2 == 1)
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
  t_philo   *philo_tab;
  t_main_th th_master;

  if (argc != 5 && argc != 6)
    return (print_error("Nb of arguments is invalid\n"), 1);
  if (check_args(argc, argv, th_master.tab_arg)) // have to init last arg
    return (2);

  // INIT MAIN THREAD FUNCTION
  th_master.ready = 0;
  th_master.is_dead = 0;
  pthread_mutex_init(&th_master.ready_mutex, NULL);
  pthread_mutex_init(&th_master.isdead_mutex, NULL);
  // INIT MAIN THREAD FUNCTION

  if (argc == 5)
  {
    philo_tab = socrate_maker(&th_master);
    if (!philo_tab)
        return (3);
    if (launcher(philo_tab, th_master.tab_arg[0]))
        return (free_all(philo_tab, th_master.tab_arg[0]), 4);


  // MAIN THREAD ROUTINE FUNCTION
    pthread_mutex_lock(&th_master.ready_mutex);
    th_master.ready = 1;
    pthread_mutex_unlock(&th_master.ready_mutex);
    while (1)
    {
      pthread_mutex_lock(&th_master.isdead_mutex);
      if (th_master.is_dead)
      {
        pthread_mutex_unlock(&th_master.isdead_mutex);
        break;
      }
      pthread_mutex_unlock(&th_master.isdead_mutex);
    }
  // MAIN THREAD ROUTINE FUNCTION



    usleep(5000);
    free_all(philo_tab, th_master.tab_arg[0]);
  }
  return (0);
}
