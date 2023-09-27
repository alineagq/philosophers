/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:01:37 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 22:10:31 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo_die(t_table *table, t_philo *philo)
{
	if (table->num_philos == 1)
	{
		print_status(philo, THINKING);
		print_status(philo, FORK);
		ft_usleep(table->time_to_die);
		philo->status = DIED;
		print_status(philo, DIED);
		return (1);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (keep_threads_alive(philo))
		return ;
	if (philo->id % 2 != 0 || philo->id == table->num_philos)
	{
		pthread_mutex_lock(&table->forks[philo->left_fork_id]);
		print_status(philo, FORK);
		pthread_mutex_lock(&table->forks[philo->right_fork_id]);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->right_fork_id]);
		print_status(philo, FORK);
		pthread_mutex_lock(&table->forks[philo->left_fork_id]);
		print_status(philo, FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	pthread_mutex_unlock(&table->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&table->forks[philo->right_fork_id]);
	print_status(philo, DROP_FORKS);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	if (keep_threads_alive(philo) && philo->eat_count == 0)
		return ;
	print_status(philo, EATING);
	philo->last_meal = get_time();
	if (philo->eat_count > 0)
		philo->eat_count--;
	ft_usleep(table->time_to_eat);
}
