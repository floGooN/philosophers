/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/25 17:40:20 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline long int  get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static inline void    print_death(t_main_th *main_th, int philo_index)
{
    const t_philo   *philo = &main_th->philo_tab[philo_index];
    int             i;

    i = -1;
    pthread_mutex_lock(&main_th->print_mutex);
    printf("%ld %d died\n", get_time() - philo->time_data.start_time, \
            philo->index);
    while (++i < philo->nb_philo)
        main_th->stop_simu[i] = 1;
    pthread_mutex_unlock(&main_th->print_mutex);
}

static void main_routine(t_main_th *main_th, int nb_philo)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&main_th->ready_mutex);
	while (!usleep(10 * nb_philo))
	{
		while (++i < nb_philo)
		{
        	if (main_th->stop_simu[i] == 1 && main_th->counter != -2)
            	return (print_death(main_th, i));
            if (main_th->counter == -2)
            {
                i = -1;
                while (++i < nb_philo)
                    main_th->stop_simu[i] = 1;
                return ;
            }
		}
		i = -1;
		if (main_th->counter == -2)
        {
            while (++i < nb_philo)
                main_th->stop_simu[i] = 1;
			return ;
        }
	}
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
