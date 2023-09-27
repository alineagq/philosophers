/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:11:24 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 22:24:02 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosopher(void)
{
	t_table	*table;
	int		i;

	table = get_table();
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = table->num_eat;
		table->philos[i].last_meal = get_time();
		table->philos[i].left_fork_id = i;
		table->philos[i].right_fork_id = (i + 1) % table->num_philos;
		table->philos[i].status = THINKING;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_status(t_philo *philo, int status)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&table->print);
	if ((table->any_philosopher_dead && philo->status != DIED))
	{
		pthread_mutex_unlock(&table->print);
		return ;
	}
	if (status == FORK)
		printf("%ld %d has taken a fork\n", get_time() - table->start_time,
			philo->id);
	if (status == DROP_FORKS)
		printf("%ld %d dropped forks\n", get_time() - table->start_time,
			philo->id);
	if (status == EATING)
		printf("%ld %d is eating\n", get_time() - table->start_time, philo->id);
	if (status == SLEEPING)
		printf("%ld %d is sleeping\n", get_time() - table->start_time,
			philo->id);
	if (status == THINKING)
		printf("%ld %d is thinking\n", get_time() - table->start_time,
			philo->id);
	if (status == DIED)
		printf("%ld %d died\n", get_time() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print);
}
