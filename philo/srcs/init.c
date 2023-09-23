/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:46:27 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 18:49:11 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_simulation(int argc, char **argv)
{
	t_table	*table;

	table = get_table();
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->num_eat = ft_atoi(argv[5]);
	else
		table->num_eat = 0;
	table->philos = NULL;
	table->start_time = get_time();
	get_table_info();
	return (EXIT_SUCCESS);
}
