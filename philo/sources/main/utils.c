/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/04 18:46:53 by florian          ###   ########.fr       */
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

void  free_all(t_philo *philo_tab, int tab_size)
{
  int  i;

  i = 0;
  if (philo_tab)
  {
    if (i == 0 && philo_tab[i].print_mutex)
      free(philo_tab[i].print_mutex);
    while (i < tab_size)
    {
      if (philo_tab[i].fork_ptr)
        free(philo_tab[i].fork_ptr);
      i++;
    }
    free(philo_tab);
  }
}
