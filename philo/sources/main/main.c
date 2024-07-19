/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:06:29 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/19 16:35:43 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int  say_ready(t_main_th *main_th)
{
    if (pthread_mutex_lock(&main_th->ready_mutex))
      return (ft_perror("error -> lock ready_mtx (say ready)\n"), 1);
    main_th->ready = 1;
    if (pthread_mutex_unlock(&main_th->ready_mutex))
      return (ft_perror("error -> unlock ready_mtx (say ready)\n"), 1);
    return (0);
}

static int main_routine(t_main_th *main_th)
{
    if (say_ready(main_th))
        return (1);
    while (1)
    {
        if (pthread_mutex_lock(&main_th->isdead_mutex))
            return (ft_perror("error -> lock isdead_mtx\n"), 1);
        if (main_th->is_dead)
        {
            if (pthread_mutex_unlock(&main_th->isdead_mutex))
            return (ft_perror("error -> unlock isdead_mtx\n"), 1);
            break;
        }
        if (pthread_mutex_unlock(&main_th->isdead_mutex))
            return (ft_perror("error -> unlock isdead_mtx\n"), 1);
        if (pthread_mutex_lock(&main_th->counter_mtx))
            return (ft_perror("error -> lock counter_mtx\n"), 1);
        if (main_th->counter == 0)
            return (pthread_mutex_unlock(&main_th->counter_mtx));
        if (pthread_mutex_unlock(&main_th->counter_mtx))
            return (ft_perror("error -> unlock counter_mtx\n"), 1);
        usleep(100);
    }
    return (0);
}

static bool launcher(t_philo *philo_tab, int tab_size, t_main_th *main_th)
{
    int  i;

    i = 0;
    while (i < tab_size)
    {
        if (pthread_create(&philo_tab[i].philo_id, NULL, routine, &philo_tab[i]))
        {
            stop_simu(NULL, main_th);
            free_all(philo_tab, i + 1, main_th);
            return (ft_perror("error -> launcher"), 1);
        }
        i++;
    }
    return (0);
}

int	main(int argc, char **argv)
{
    int         tab_arg[5];
    t_philo     *philo_tab;
    t_main_th   main_th;

    if (argc != 5 && argc != 6)
        return (ft_perror("Nb of arguments is invalid\n"), 1);
    if (check_args(argc, argv, tab_arg))
        return (2);
    init_main_thread(&main_th, tab_arg[0], argc);
    if (argc == 5)
        philo_tab = socrate_maker(&main_th, tab_arg, 0);
    else
        philo_tab = socrate_maker(&main_th, tab_arg, 1);
    if (!philo_tab)
        return (3);
    if (launcher(philo_tab, tab_arg[0], &main_th))
        return (4);
    if (main_routine(&main_th))
    {
        stop_simu(NULL, &main_th);
        return (free_all(philo_tab, tab_arg[0], &main_th), 5);
    }
    free_all(philo_tab, tab_arg[0], &main_th);
    return (0);
}
