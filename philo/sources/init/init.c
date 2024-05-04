/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/04 09:01:56 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "init.h"

#include <stdio.h>
#include <string.h>

static void  ft_memcpy(void *dst, const void *src, int size)
{
  int  i;

  i = 0;
  while (i < size)
  {
    ((char *)dst)[i] = ((char *)src)[i];
    i++;
  }
}

static bool  init_philo(t_philo **tab, int tab_size, pthread_mutex_t **print)
{
  *tab = ft_calloc(sizeof(t_philo), tab_size);
  if (!*tab)
    return (print_error(TAB_ERROR), 1);
  *print = malloc(sizeof(pthread_mutex_t));
  if (!*print)
    return (free_all(*tab, 0, NULL), print_error(TAB_ERROR), 1);
  pthread_mutex_init(*print, NULL);
  return (0);
}

t_check *checker_init(int tab_size, bool *ready, void **ret_value)
{
  t_check *tab;
  int  i;

  i = 0;
  tab = ft_calloc(sizeof(t_check), tab_size);
  if (!tab)
    return (NULL);
  while (i < tab_size)
  {
    tab[i].ready_ptr = ready;
    tab[i].ret_value = ret_value;
    i++;
  }
  return (tab);
}

t_philo	*socrate_maker(int *tab_args, bool *ready_ptr)
{
	t_philo	        *tab;
  pthread_mutex_t *print;
  int          i;

  i = 0;
  if (init_philo(&tab, tab_args[0], &print))
    return (NULL);
  while (i < tab_args[0])
  {
    tab[i].print_mutex = print;
    tab[i].args = malloc(5 * sizeof(int));
    tab[i].fork_ptr = malloc(sizeof(t_fork));
    if (!tab[i].args || !tab[i].fork_ptr)
      return (free_all(tab, (i + 1), NULL), print_error(TAB_ERROR), NULL);
    tab[i].index = i;
    tab[i].time_to_die = tab_args[1];
    tab[i].nb_meal = tab_args[4];
    tab[i].ready = ready_ptr;
    ft_memcpy(tab[i].args, tab_args, (5 * sizeof(int)));
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[0], NULL);
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[1], NULL);
    i++;
  }
  return (tab);
}
