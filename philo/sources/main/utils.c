/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/03 22:59:28 by florian          ###   ########.fr       */
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

void  free_philo(t_philo *philo_tab, size_t tab_size)
{
  size_t  i;

  i = 0;
  if (!philo_tab)
    return ;
  while (i < tab_size)
  {
    if (i == 0 && philo_tab[i].print_mutex)
      free(philo_tab[i].print_mutex);
    if (philo_tab[i].args)
      free(philo_tab[i].args);
    if (philo_tab[i].fork_ptr)
      free(philo_tab[i].fork_ptr);
  }
  free(philo_tab);
}
