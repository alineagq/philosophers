/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:42:16 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 18:04:46 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (keep_threads_alive(philo))
		return ;
	print_status(philo, SLEEPING);
	ft_usleep(table->time_to_sleep);
	philo->status = THINKING;
}
