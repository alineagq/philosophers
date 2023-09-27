/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:26:04 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/27 12:11:27 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	keep_threads_alive(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&table->data);
	if (table->any_philosopher_dead)
	{
		pthread_mutex_unlock(&table->data);
		return (1);
	}
	else if (get_time() - philo->last_meal > table->time_to_die)
	{
		print_status(philo, DIED);
		table->any_philosopher_dead = 1;
		pthread_mutex_unlock(&table->data);
		return (1);
	}
	pthread_mutex_unlock(&table->data);
	return (0);
}

int	check_death(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (get_time() - philo->last_meal >= table->time_to_die)
	{
		print_status(philo, DIED);
		table->any_philosopher_dead = 1;
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	table = get_table();
	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (one_philo_die(table, philo))
		return (NULL);
	if (philo->id % 2 == 1)
		thinking(philo);
	while (!keep_threads_alive(philo) && (philo->eat_count == -1
			|| philo->eat_count > 0))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	all_philosophers_have_eaten(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (table->num_eat == 0)
			return (0);
		if (table->philos[i].eat_count < table->num_eat + 1)
			return (0);
	}
	return (1);
}

void	run_simulation(void)
{
	int		i;
	t_table	*table;

	table = get_table();
	i = 0;
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, routine,
			&table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	usleep(500);
	clean_simulation();
	exit(EXIT_SUCCESS);
}
