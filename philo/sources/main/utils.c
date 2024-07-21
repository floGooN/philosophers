/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/21 13:24:15 by fberthou         ###   ########.fr       */
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

int	ft_perror(const char *str)
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

void	free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th)
{
	int	i;

	i = 0;
	while (i < tab_size)
	{
		if (pthread_join(philo_tab[i].philo_id, NULL))
		{
			ft_perror("error -> join thread\n");
			return ;
		}
		pthread_mutex_destroy(philo_tab[i].shared_mtx.stop_mtx);
		pthread_mutex_destroy(philo_tab[i].shared_mtx.right_fork);
		i++;
	}
	pthread_mutex_destroy(&main_th->ready_mutex);
	pthread_mutex_destroy(&main_th->print_mutex);
	pthread_mutex_destroy(&main_th->counter_mtx);
	free(philo_tab);
	free(main_th->stop_simu);
	free(main_th->stop_mtx);
	free(main_th->all_forks);
}
