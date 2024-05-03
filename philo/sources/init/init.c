/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 21:47:23 by florian          ###   ########.fr       */
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

static void init_var(t_philo *curr_philo)
{
  static size_t i = 1;

  curr_philo->time_to_die = curr_philo->args[1];
  curr_philo->time_to_eat = curr_philo->args[2];
  curr_philo->time_to_sleep = curr_philo->args[3];
  curr_philo->nb_meal = curr_philo->args[4];
  curr_philo->index = i;
  i++;
}

static bool init_mutex(t_philo *curr_philo, bool is_head)
{
  if (is_head)
  {
    curr_philo->print_mutex = malloc(sizeof(pthread_mutex_t));
    if (!curr_philo->print_mutex)
      return (1);
    pthread_mutex_init(curr_philo->print_mutex, NULL);
  }
  else
    curr_philo->print_mutex = curr_philo->head_lst->print_mutex;
  pthread_mutex_init(&curr_philo->fork_ptr->fork_mutex[0], NULL);
  pthread_mutex_init(&curr_philo->fork_ptr->fork_mutex[1], NULL);
  return (0);
}

static bool init_head_lst(t_philo **head, int *tab_args)
{
  init_var(*head);
  if (init_mutex(*head, 1))
    return (free_lst(*head), print_error(LST_ERROR), 1);
  return (0);
}

t_philo	*socrate_maker(int *tab_args, bool *ready_ptr)
{
	t_philo	        *tab;
  size_t          i;
  pthread_mutex_t *print;

  i = 0;
  tab = ft_calloc(sizeof(t_philo), tab_args[0]);
  if (!tab)
    return (NULL);
  print = malloc(sizeof(pthread_mutex_t));
  if (!print)
    return (free_philo(tab, 0), NULL);
  pthread_mutex_init(print, NULL);
  while (i < tab_args[0])
  {
    tab[i].args = malloc(5 * sizeof(int *));
    tab[i].fork_ptr = malloc(sizeof(t_fork));
    if (!tab[i].args || !tab[i].fork_ptr)
      return (free_philo(tab, tab_args[0]), NULL);
    tab[i].index = i;
    tab[i].time_to_die = tab_args[1];
    tab[i].nb_meal = tab_args[4];
    tab[i].ready = ready_ptr;
    tab[i].print_mutex = print;
    ft_memcpy(tab[i].args, tab_args, (5 * sizeof(int *)));
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[0], NULL);
    pthread_mutex_init(&tab[i].fork_ptr->fork_mutex[1], NULL);
  }
  return (tab);
}
