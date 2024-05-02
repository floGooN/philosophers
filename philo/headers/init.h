/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:59 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/02 18:18:02 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <stdlib.h>

# define MUTEX_ERROR "Error -> init mutex\n"
# define LST_ERROR   "Error -> init list\n"

void	*ft_calloc(size_t nmemb, size_t size);
void    free_lst(t_philo *head_lst);
int		print_error(char *str);

#endif
