/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:54:39 by florian           #+#    #+#             */
/*   Updated: 2024/07/15 16:59:13 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <struct.h>

//  ==== main/utils.c ====  //
int		print_error(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void    free_all(t_philo *philo_tab, int tab_size);

//  ==== check_args/check_args.c ====  //
int		check_args(int argc, char **argv, int *tab_arg);

// ==== main/init.c ====  //
void    init_main_thread(t_main_th *main_th);
t_philo *socrate_maker(t_main_th *main_th, int tab_args[]);

// ==== simulation/philo.c ====  //
void    *odd_routine(void *arg);
void    *even_routine(void *arg);

//  ==== check_args/check_utils.c ====  //
long	ft_atoi(const char *nptr);

//  ==== simulaation/actions.c ====  //
bool      eat_act(t_philo *philo);
bool      sleep_act(t_philo *philo);
bool      think_act(void *arg);

//  ==== simulaation/simu_utils.c ====  //
bool      print_message(t_philo *philo, int action);
void      ft_usleep(long time);
long int  get_time(void);
bool      check_death(t_philo *philo);

// # define GET_TIME(result)   struct timeval	tv; \
// 	                        if (gettimeofday(&tv, NULL)) \
//                             { \
//                                 print_error("GET_TIME FAIL\n"); \
// 		                        result = -1; \
//                             } \
//                             else \
//                                 result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); \

// # define FT_USLEEP(time)    long int	start; \
//                             GET_TIME(start); \
//                             while ((GET_TIME(time) - start) < time) \
//                                 usleep(time / 10)

#endif
