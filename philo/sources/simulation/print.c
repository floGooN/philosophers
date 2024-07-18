/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:54:31 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/18 16:20:35 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool  print_message(char *msg, t_philo *philo, bool is_dead)
{
    if (pthread_mutex_lock(philo->shared_mtx.print_mtx))
      return (ft_perror("error -> lock mtx (print_message)\n"), 1);
    if (check_death(philo))
      return (pthread_mutex_unlock(philo->shared_mtx.print_mtx), 1);
    printf("%ld %d %s\n", get_time() - philo->time_data.start_time, \
          philo->index, msg);
    if (is_dead)
      change_death_status(philo);

    if (pthread_mutex_unlock(philo->shared_mtx.print_mtx))
      return (ft_perror("error -> unlock mtx (print_message)\n"), 1);
    return (0);
}
