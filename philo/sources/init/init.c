/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/13 17:26:49 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "init.h"

#include <stdio.h>
#include <string.h>

// static bool  init_philo(t_philo **tab, int tab_size, pthread_mutex_t **print)
// {
  
//   // *print = malloc(sizeof(pthread_mutex_t));
//   // if (!*print)
//   //   return (free_all(*tab, 0), print_error(TAB_ERROR), 1);
//   // pthread_mutex_init(*print, NULL);
//   return (0);
// }

t_philo	*socrate_maker(int tab_args[], bool *ready_ptr, bool *is_dead, \
                                        pthread_mutex_t *ready_isdead_mutex)
{
  pthread_mutex_t *print;
	t_philo	        *tab;
  int             i;

  i = 0;
  tab = ft_calloc(sizeof(t_philo), tab_args[0]);
  if (!tab)
    return (print_error(TAB_ERROR), NULL);
  print = malloc(sizeof(pthread_mutex_t));
  if (!print)
    return (free(tab), print_error(TAB_ERROR), NULL);
  pthread_mutex_init(print, NULL);
  while (i < tab_args[0])
  {
    tab[i].print_mutex = print;
    tab[i].ready_mutex = &ready_isdead_mutex[0];
    tab[i].isdead_mutex = &ready_isdead_mutex[1];
    pthread_mutex_init(&tab[i].fork_mutex, NULL);
    tab[i].fork = 1;
    tab[i].index = i;
    tab[i].time_to_die = tab_args[1];
    tab[i].nb_meal = tab_args[4];
    tab[i].ready = ready_ptr;
    tab[i].is_dead = is_dead;
    tab[i].args = tab_args;
    i++;
  }
  return (tab);
}
