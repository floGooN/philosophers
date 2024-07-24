/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/22 16:43:52 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_mtx(t_philo *philo_tab, t_main_th *main_th, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo_tab[i].shared_mtx.ready_mtx = &main_th->ready_mutex;
		philo_tab[i].shared_mtx.end_mtx = &main_th->end_mutex;
		philo_tab[i].shared_mtx.print_mtx = &main_th->print_mutex;
		philo_tab[i].shared_mtx.counter_mtx = &main_th->counter_mtx;
		philo_tab[i].shared_mtx.stop_mtx = &main_th->stop_mtx[i];
		philo_tab[i].shared_mtx.right_fork = &main_th->all_forks[i];
		if (i == nb_philo - 1)
			philo_tab[i].shared_mtx.left_fork = &main_th->all_forks[0];
		else
			philo_tab[i].shared_mtx.left_fork = &main_th->all_forks[i + 1];
		i++;
	}
}

static void	init_time(t_time *time_data, int tab_arg[], int argc)
{
	time_data->time_to_die = tab_arg[1];
	time_data->time_to_eat = tab_arg[2];
	time_data->time_to_sleep = tab_arg[3];
	if (argc == 6)
		time_data->nb_meal = tab_arg[4];
	else
		time_data->nb_meal = -1;
}

void	socrate_maker(t_main_th *main_th, int tab_arg[], int argc)
{
	int	nb_philo;
	int	i;

	i = 0;
	nb_philo = tab_arg[0];
	while (i < nb_philo)
	{
		main_th->philo_tab[i].index = i + 1;
		main_th->philo_tab[i].counter = &main_th->counter;
		main_th->philo_tab[i].nb_philo = tab_arg[0];
		main_th->philo_tab[i].stop_simu = &main_th->stop_simu[i];
		main_th->philo_tab[i].right_fork = 1;
		if (i == nb_philo - 1)
			main_th->philo_tab[i].left_fork = &main_th->philo_tab[0].right_fork;
		else
			main_th->philo_tab[i].left_fork = &main_th->philo_tab[i
				+ 1].right_fork;
		init_time(&main_th->philo_tab[i].time_data, tab_arg, argc);
		i++;
	}
	init_mtx(main_th->philo_tab, main_th, nb_philo);
}

static int	alloc_tab(t_main_th *main_th, int nb_philo)
{
	main_th->philo_tab = ft_calloc(nb_philo, sizeof(t_philo));
	if (!main_th->philo_tab)
		return (ft_perror("error -> alloc_tab()"), -1);
	main_th->stop_simu = ft_calloc(nb_philo, sizeof(bool));
	if (!main_th->stop_simu)
	{
		free(main_th->philo_tab);
		return (ft_perror("error -> alloc_tab()"), -1);
	}
	main_th->stop_mtx = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (!main_th->stop_mtx)
	{
		free(main_th->philo_tab);
		free(main_th->stop_simu);
		return (ft_perror("error -> alloc_tab()"), -1);
	}
	main_th->all_forks = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (!main_th->all_forks)
	{
		free(main_th->philo_tab);
		free(main_th->stop_simu);
		free(main_th->stop_mtx);
		return (ft_perror("error -> alloc_tab()"), -1);
	}
	return (0);
}

int	init_main_thread(t_main_th *main_th, int nb_philo, int argc)
{
	int	i;

	i = 0;
	if (alloc_tab(main_th, nb_philo))
		return (-1);
	if (argc == 6)
		main_th->counter = nb_philo;
	else
		main_th->counter = -1;
	pthread_mutex_init(&main_th->ready_mutex, NULL);
	pthread_mutex_init(&main_th->end_mutex, NULL);
	pthread_mutex_init(&main_th->print_mutex, NULL);
	pthread_mutex_init(&main_th->counter_mtx, NULL);
	while (i < nb_philo)
	{
		pthread_mutex_init(&main_th->stop_mtx[i], NULL);
		pthread_mutex_init(&main_th->all_forks[i], NULL);
		i++;
	}
    pthread_mutex_lock(&main_th->end_mutex);
	return (pthread_mutex_lock(&main_th->ready_mutex));
}
