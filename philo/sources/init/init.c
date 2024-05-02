/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 22:30:44 by florian          ###   ########.fr       */
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
  curr_philo->nb_lunch = curr_philo->args[4];
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
	*head = ft_calloc(1, sizeof(t_philo));
	if (!*head)
		return (print_error(LST_ERROR), 1);
  (*head)->fork_ptr = ft_calloc(1, sizeof(t_fork));
  if (!(*head)->fork_ptr)
    return (free_lst(*head), print_error(LST_ERROR), 1);
  (*head)->args = ft_calloc(sizeof(int *), 5);
  (*head)->ready = ft_calloc(sizeof(bool), 1);
  if (!(*head)->args || !(*head)->ready)
    return (free_lst(*head), print_error(LST_ERROR), 1);
  (*head)->head_lst = *head;
  ft_memcpy((*head)->args, tab_args, (5 * sizeof(int *)));
  init_var(*head);
  if (init_mutex(*head, 1))
    return (free_lst(*head), print_error(LST_ERROR), 1);
  return (0);
}

t_philo	*socrate_maker(int *tab_args)
{
	t_philo	*lst;
	t_philo	*head;

  if (init_head_lst(&head, tab_args))
    return (NULL);
	lst = head;
	while (--(tab_args[0]) > 0)
	{
		lst->next = ft_calloc(1, sizeof(t_philo));
		if (!lst->next)
			return (free_lst(head), print_error(LST_ERROR), NULL);
    lst = lst->next;
    lst->fork_ptr = ft_calloc(1, sizeof(t_fork));
    if (!lst->fork_ptr)
      return (free_lst(head), print_error(LST_ERROR), NULL);
    lst->args = ft_calloc(sizeof(int *), 5);
    if (!lst->args)
      return (free_lst(head), print_error(LST_ERROR), NULL);
    lst->head_lst = head;
    lst->ready = head->ready;
    ft_memcpy(lst->args, tab_args, (5 * sizeof(int *)));
    init_var(lst);
    init_mutex(lst, 0);
  }
	return (head);
}
