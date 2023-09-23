/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:11:24 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 19:37:20 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosopher(t_philo *philosopher, int id,
		pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	t_table	*t_table;

	t_table = get_table();
	philosopher->id = id;
	philosopher->state = THINKING;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->eat_count = 0;
	philosopher->last_meal = t_table->start_time;
	philosopher->next = NULL;
}
