/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 22:59:48 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "init.h"

#include <stdio.h>
#include <string.h>

static void  ft_memcpy(void *dst, const void *src, size_t size)
{
  size_t  i;

  i = 0;
  while (i < size)
  {
    ((char *)dst)[i] = ((char *)src)[i];
    i++;
  }
}

static bool  init_philo(t_philo **tab, size_t tab_size, pthread_mutex_t **print)
{
  *tab = ft_calloc(sizeof(t_philo), tab_size);
  if (!*tab)
    return (1);
  *print = malloc(sizeof(pthread_mutex_t));
  if (!*print)
    return (free_philo(*tab, 0), 1);
  pthread_mutex_init(*print, NULL);
  return (0);
}

t_philo	*socrate_maker(int *tab_args, bool *ready_ptr)
{
	t_philo	        *tab;
  pthread_mutex_t *print;
  size_t          i;

  i = 0;
  if (init_philo(&tab, tab_args[0], &print))
    return (NULL);
  while (i < tab_args[0])
  {
    tab[i].args = malloc(5 * sizeof(int));
    tab[i].fork_ptr = malloc(sizeof(t_fork));
    if (!tab[i].args || !tab[i].fork_ptr)
      return (free_philo(tab, tab_args[0]), NULL);
    tab[i].index = i;
    tab[i].time_to_die = tab_args[1];
    tab[i].nb_meal = tab_args[4];
    tab[i].ready = ready_ptr;
    tab[i].print_mutex = print;
    ft_memcpy(tab[i].args, tab_args, (5 * sizeof(int)));
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[0], NULL);
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[1], NULL);
    i++;
  }
  return (tab);
}
