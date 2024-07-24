/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 18:55:17 by florian          ###   ########.fr       */
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
		main_th->philo_tab[i].nb_philo = tab_arg[0];
		main_th->philo_tab[i].shared_res.right_fork = 1;
		if (i == nb_philo - 1)
			main_th->philo_tab[i].shared_res.left_fork = \
            &main_th->philo_tab[0].shared_res.right_fork;
		else
			main_th->philo_tab[i].shared_res.left_fork = \
            &main_th->philo_tab[i + 1].shared_res.right_fork;
		main_th->philo_tab[i].shared_res.stop_simu = &main_th->stop_simu;
		main_th->philo_tab[i].shared_res.counter = &main_th->counter;
		init_time(&main_th->philo_tab[i].time_data, tab_arg, argc);
		i++;
	}
	init_mtx(main_th->philo_tab, main_th, nb_philo);
}

int	init_main_thread(t_main_th *main_th, int nb_philo, int argc)
{
    main_th->philo_tab = ft_calloc(nb_philo, sizeof(t_philo));
    main_th->stop_simu = 0;
	if (!main_th->philo_tab)
		return (ft_perror("error -> alloc_tab()"), -1);
	if (argc == 6)
		main_th->counter = nb_philo;
	else
		main_th->counter = -1;
	pthread_mutex_init(&main_th->ready_mutex, NULL);
	pthread_mutex_init(&main_th->end_mutex, NULL);
	pthread_mutex_init(&main_th->print_mutex, NULL);
    pthread_mutex_lock(&main_th->end_mutex);
    pthread_mutex_lock(&main_th->ready_mutex);
	return (0);
}
