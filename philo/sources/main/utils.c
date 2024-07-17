/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/17 08:45:56 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	print_error(const char *str)
{
	return (write(2, str, ft_strlen(str)));
}

void    *ft_calloc(size_t nmemb, size_t size)
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

void  free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th)
{
  int  i;

  i = 0;
  if (philo_tab && tab_size > 0)
  {
	pthread_mutex_destroy(philo_tab[i].shared_mtx.print_mtx);
	pthread_mutex_destroy(philo_tab[i].shared_mtx.ready_mtx);
	pthread_mutex_destroy(philo_tab[i].shared_mtx.isdead_mtx);
    while (i < tab_size)
    {
		pthread_mutex_destroy(philo_tab[i].shared_mtx.right_fork);
		i++;
    }
	// free(philo_tab[0].shared_mtx.all_forks);
	// free(philo_tab[0].shared_mtx.print_mtx);
    free(philo_tab);
  }
}
