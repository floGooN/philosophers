/*
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
    HEADER 42
*/
#include "struct.h"
#include "init.h"

# include <stdio.h>
# include <string.h>

static bool init_head_lst(t_philo **head, int *tab_args)
{
	*head = ft_calloc(1, sizeof(t_philo));
	if (!*head)
		return (print_error(LST_ERROR), 1);
  (*head)->fork_ptr = ft_calloc(1, sizeof(t_fork));
  if (!(*head)->fork_ptr)
    return (free_lst(*head), print_error(LST_ERROR), 1);
  (*head)->args = ft_calloc(sizeof(int *), 5);
  if (!(*head)->args)
    return (free_lst(*head), print_error(LST_ERROR), 1);
  memcpy((*head)->args, tab_args, (5 * sizeof(int *)));

	pthread_mutex_init(&(*head)->fork_ptr->fork_mutex, NULL);
	pthread_mutex_init(&(*head)->shared_mutex[0], NULL);
	pthread_mutex_init(&(*head)->shared_mutex[1], NULL);

  (*head)->index = 1;
  (*head)->head_lst = *head;
  return (0);
}

t_philo	*socrate_maker(int *tab_args)
{
	t_philo	*lst;
	t_philo	*head;
	int 		nb_philo;

  int i = 2;

  if (init_head_lst(&head, tab_args))
    return (NULL);
	lst = head;
	nb_philo = (tab_args[0] - 1);
	while (nb_philo-- > 0)
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
    memcpy(lst->args, tab_args, (5 * sizeof(int *)));
    pthread_mutex_init(&lst->fork_ptr->fork_mutex, NULL);
    lst->shared_mutex[0] = head->shared_mutex[0];
    lst->shared_mutex[1] = head->shared_mutex[1];
    lst->head_lst = head;
    lst->index = i++;
  }
	return (head);
}
