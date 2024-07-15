/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:30 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/09 17:42:56 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void    *ft_calloc(size_t nmemb, size_t size);
int		print_error(char *str);

static int init_tab(t_philo **tab, int tab_size, pthread_mutex_t **print)
{
    *tab = ft_calloc(sizeof(t_philo), tab_size);
    if (!*tab)
        return (print_error("error -> alloc philo_tab\n"), 1);
    *print = malloc(sizeof(pthread_mutex_t));
    if (!*print)
        return (free(*tab), print_error("error -> alloc print_mutex\n"), 1);
    pthread_mutex_init(*print, NULL);
    return (0);
}

t_philo	*socrate_maker(t_main_th *th)
{
    pthread_mutex_t *print;
	t_philo	        *tab;
    int             i;

    i = 0;
    if (init_tab(&tab, th->tab_arg[0], &print))
        return (NULL);
    while (i < th->tab_arg[0])
    {
        tab[i].print_mutex = print;
        tab[i].ready_mutex = &th->ready_mutex;
        tab[i].isdead_mutex = &th->isdead_mutex;
        pthread_mutex_init(&tab[i].fork_mutex, NULL);
        tab[i].fork = 1;
        tab[i].index = i + 1;
        tab[i].time_to_die = th->tab_arg[1];
        tab[i].nb_meal = th->tab_arg[4];
        tab[i].ready = &th->ready;
        tab[i].is_dead = &th->is_dead;
        tab[i].args = th->tab_arg;
        i++;
    }
    return (tab);
}
