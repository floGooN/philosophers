/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:54:39 by florian           #+#    #+#             */
/*   Updated: 2024/07/25 16:15:00 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//  ==== check_args/check_args.c ====  //
int		check_args(int argc, char **argv, int *tab_arg);

//  ==== check_args/check_utils.c ====  //
long	ft_atoi(const char *nptr);

// ==== main/init.c ====  //
void	socrate_maker(t_main_th *main_th, int tab_args[], int argc);
int		init_main_thread(t_main_th *main_th, int nb_philo, int argc);

//  ==== main/utils.c ====  //
int	       ft_perror(const char *str);
void       *ft_calloc(size_t nmemb, size_t size);
void       free_all(t_philo *philo_tab, int tab_size, t_main_th *main_th);

// ==== simulation/philo.c ====  //
void    *routine(void *arg);

//  ==== simulation/action.c ====  //
void    update_time(t_philo *philo);
void    drop_forks(t_philo *philo);
void    ft_usleep(long int time, atomic_int *stop);

//  ==== simulation/simu_utils.c ====  //
void    print_end(t_philo *philo);
void    wait_everybody_pls(t_philo *philo);
void    *end_of_loop(t_philo *philo);

#endif
