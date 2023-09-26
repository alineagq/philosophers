/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:26:04 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 01:26:25 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	keep_threads_alive(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_lock(&table->death_mutex);
	if (table->any_philosopher_dead)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	else if (table->all_philosophers_finished_eating)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	else if (get_time() - philo->last_meal > table->time_to_die)
	{
		print_status(philo, DIED);
		table->any_philosopher_dead = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	else if (table->num_eat != -1 && all_philosophers_have_eaten(table))
	{
		table->all_philosophers_finished_eating = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	else if (philo->status == DIED)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	table = get_table();
	philo = (t_philo *)arg;
	if (one_philo_die(table, philo))
		return (NULL);
	while (1)
	{
		if (keep_threads_alive(philo))
			return (NULL);
		if (philo->status == THINKING)
		{
			print_status(philo, THINKING);
			ft_usleep(1);
			philo->status = EATING;
			if (keep_threads_alive(philo))
				return (NULL);
		}
		if (philo->status == EATING)
		{
			if (keep_threads_alive(philo))
				return (NULL);
			eat(philo);
			pthread_mutex_lock(&table->death_mutex);
			if (philo->eat_count == table->num_eat)
			{
				table->all_philosophers_finished_eating = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_mutex);
		}
		if (philo->status == SLEEPING)
		{
			sleeping(philo);
		}
	}
	return (NULL);
}

int	all_philosophers_have_eaten(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (table->philos[i].eat_count < table->num_eat)
		{
			return (0);
		}
	}
	return (1);
}

void	run_simulation(void)
{
	t_table *table;
	int i;

	table = get_table();
	i = 0;
	pthread_mutex_init(&table->died, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->print, NULL);
	table->start_time = get_time();
	while (i < table->num_philos)
	{
		table->philos[i].last_meal = table->start_time;
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
	pthread_mutex_destroy(&table->died);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print);
	clean_simulation();
	exit(EXIT_SUCCESS);
}