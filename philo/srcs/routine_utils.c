/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/22 11:10:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int get_time(void)
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL) == -1)
        return (write(2, "gettimeofday error\n", 19), 0);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(int ms)
{
    int             start;

    start = get_time();
    while (get_time() - start < ms)
        usleep(500);
}
