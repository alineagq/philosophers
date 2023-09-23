/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:11:26 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 18:55:03 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*get_table(void)
{
	static t_table	table;

	return (&table);
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
