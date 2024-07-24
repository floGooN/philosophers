/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/24 16:24:03 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	print_death(t_main_th *main_th, int nb_philo, t_philo curr_philo)
{
	int	i;

	pthread_mutex_lock(&main_th->print_mutex);
	i = 0;
	printf("%ld %d died\n", get_time() - curr_philo.time_data.start_time,
		curr_philo.index);
	while (i < nb_philo)
	{
		pthread_mutex_lock(&main_th->stop_mtx[i]);
		main_th->stop_simu[i] = 1;
		pthread_mutex_unlock(&main_th->stop_mtx[i]);
		i++;
	}
	pthread_mutex_unlock(&main_th->print_mutex);
	return (0);
}

static int	main_routine(t_main_th *main_th, int nb_philo)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&main_th->ready_mutex);
	while (1)
	{
		while (++i < nb_philo)
		{
			pthread_mutex_lock(&main_th->stop_mtx[i]);
			if (main_th->stop_simu[i] == 1)
			{
				pthread_mutex_unlock(&main_th->stop_mtx[i]);
				return (print_death(main_th, nb_philo, main_th->philo_tab[i]));
			}
            if (main_th->stop_simu[i] == -2)
                return (0);
			pthread_mutex_unlock(&main_th->stop_mtx[i]);
		}
		pthread_mutex_lock(&main_th->counter_mtx);
		if (!main_th->counter)
			return (pthread_mutex_unlock(&main_th->counter_mtx));
		pthread_mutex_unlock(&main_th->counter_mtx);
		i = -1;
		usleep(100);
	}
	return (0);
}

static bool	launcher(t_philo *philo_tab, int tab_size, t_main_th *main_th)
{
	int	i;

	i = 0;
	while (i < tab_size)
	{
		if (pthread_create(&philo_tab[i].philo_id, NULL, routine, \
            &philo_tab[i]))
		{
			free_all(philo_tab, i + 1, main_th);
			return (ft_perror("error -> launcher\n"), 1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			tab_arg[5];
	t_main_th	main_th;

	if (argc != 5 && argc != 6)
		return (ft_perror("Nb of arguments is invalid\n"), 1);
	if (check_args(argc, argv, tab_arg))
		return (2);
	if (init_main_thread(&main_th, tab_arg[0], argc))
		return (3);
	socrate_maker(&main_th, tab_arg, argc);
	if (launcher(main_th.philo_tab, tab_arg[0], &main_th))
		return (4);
	main_routine(&main_th, tab_arg[0]);
	free_all(main_th.philo_tab, tab_arg[0], &main_th);
	return (0);
}
