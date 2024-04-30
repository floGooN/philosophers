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

static bool init_head_lst(t_philo **head, int *tab_args)
{
	*head = ft_calloc(1, sizeof(t_philo));
	if (!*head)
		return (print_error(LST_ERROR), 1);
  (*head)->fork_ptr = ft_calloc(1, sizeof(t_fork));
  if (!(*head)->fork_ptr)
    return (free(*head), print_error(LST_ERROR), 1);
	(*head)->args = tab_args;
	if (pthread_mutex_init(&(*head)->fork_ptr->mutex, NULL))
    return (free_lst(*head), print_error(LST_ERROR), 1);
  return (0);
}

t_philo	*socrate_maker(int *tab_args)
{
	t_philo	*lst;
	t_philo	*head;
	int 		nb_philo;

  if (init_head_lst(&head, tab_args))
    return (NULL);
	lst = head;
	nb_philo = tab_args[0] - 1;
	while (nb_philo--)
	{
		lst->next = ft_calloc(1, sizeof(t_philo));
		if (!lst->next)
			return (free_lst(head), print_error(LST_ERROR), NULL);
    lst = lst->next;
    lst->fork_ptr = ft_calloc(1, sizeof(t_fork));
    if (!lst->fork_ptr)
      return (free_lst(head), print_error(LST_ERROR), NULL);
    lst->args = tab_args;
    if (pthread_mutex_init(&lst->fork_ptr->mutex, NULL))
      return (free_lst(head), print_error(LST_ERROR), NULL);
	}
	return (head);
}
