/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 22:27:32 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i++])
		;
	return (i);
}

int	print_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_mem_place;
	size_t	total_memory_size;

	total_memory_size = nmemb * size;
	if (total_memory_size == 0 || (total_memory_size / nmemb != size))
		return (NULL);
	new_mem_place = malloc(total_memory_size);
	if (!new_mem_place)
		return (NULL);
	memset(new_mem_place, 0, total_memory_size);
	return (new_mem_place);
}

void  free_lst(t_philo *head_lst)
{
  t_philo *tmp;
  bool     state;

  state = 0;
  while (head_lst)
  {
    tmp = head_lst->next;
    if (head_lst->fork_ptr)
      free(head_lst->fork_ptr);
    if (head_lst->args)
      free(head_lst->args);
	  if (head_lst->index == 1)
      free(head_lst->print_mutex);
		free(head_lst->ready);
    free(head_lst);
    head_lst = tmp;
  }
}
