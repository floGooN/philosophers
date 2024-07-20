/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:51:26 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/20 11:03:48 by fberthou         ###   ########.fr       */
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

int	stop_simu(t_philo *philo_tab, t_main_th *main_th)
{
	if (main_th)
	{
		if (pthread_mutex_lock(&main_th->isdead_mutex))
			return (ft_perror("error -> lock mtx (stop_simu)\n"), 1);
		main_th->is_dead = 1;
		if (pthread_mutex_unlock(&main_th->isdead_mutex))
			return (ft_perror("error -> unlock mtx (stop_simu)\n"), 1);
	}
	else if (philo_tab)
	{
		if (pthread_mutex_lock(philo_tab->shared_mtx.isdead_mtx))
			return (ft_perror("error -> lock mtx (stop_simu)\n"), 1);
		*(philo_tab->is_dead) = 1;
		if (pthread_mutex_unlock(philo_tab->shared_mtx.isdead_mtx))
			return (ft_perror("error -> unlock mtx (stop_simu)\n"), 1);
	}
	return (0);
}

void	free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th)
{
	int	i;

	i = 0;
	while (i < tab_size)
	{
		if (pthread_join(philo_tab[i].philo_id, NULL))
			ft_perror("error -> join thread\n");
		i++;
	}
	i = 0;
	pthread_mutex_destroy(philo_tab[i].shared_mtx.print_mtx);
	pthread_mutex_destroy(philo_tab[i].shared_mtx.ready_mtx);
	pthread_mutex_destroy(philo_tab[i].shared_mtx.isdead_mtx);
	free(philo_tab[i].shared_mtx.print_mtx);
	while (i < tab_size)
	{
		pthread_mutex_destroy(philo_tab[i].shared_mtx.right_fork);
		i++;
	}
	free(main_th->all_forks);
	free(philo_tab);
}
