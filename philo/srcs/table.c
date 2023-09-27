/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:11:26 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 22:23:40 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*get_table(void)
{
	static t_table	table;

	return (&table);
}

int	init_table(int argc, char **argv)
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
		table->num_eat = -1;
	table->philos = NULL;
	table->forks = NULL;
	table->any_philosopher_dead = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		error("Error: malloc failed.\n", EXIT_FAILURE);
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		error("Error: malloc failed.\n", EXIT_FAILURE);
	pthread_mutex_init(&table->data, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->died, NULL);
	return (EXIT_SUCCESS);
}

void	get_table_info(void)
{
	t_table	*table;

	table = get_table();
	if (table->num_philos == 1)
		printf("🔮 - %d philosopher is sitting at the table.\n",
			table->num_philos);
	else if (table->num_philos > 1)
		printf("🔮 - %d philosophers are sitting at the table.\n",
			table->num_philos);
	printf("⏰ - Time to die: %d\n", table->time_to_die);
	printf("🍝 - Time to eat: %d\n", table->time_to_eat);
	printf("💤 - Time to sleep: %d\n", table->time_to_sleep);
	if (table->num_eat)
		printf("🍽️  - Number of times each philosopher must eat: %d\n",
			table->num_eat);
	printf("Starting simulation...\n");
	printf("Start time: %ld\n", get_time() - table->start_time);
}
