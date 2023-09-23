/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:46:27 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 19:56:39 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	init_table(int argc, char **argv)
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
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (EXIT_FAILURE);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_simulation(int argc, char **argv)
{
	t_table	*table;

	table = get_table();
	init_table(argc, argv);
	init_philosophers();
	get_table_info();
	return (EXIT_SUCCESS);
}
