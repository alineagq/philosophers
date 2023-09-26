/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:42:16 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/25 22:38:56 by aqueiroz         ###   ########.fr       */
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

static void	take_forks(t_philo *philo, pthread_mutex_t *forks, int left_fork_id,
		int right_fork_id)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&forks[left_fork_id]);
		print_status(philo, FORK);
		pthread_mutex_lock(&forks[right_fork_id]);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&forks[right_fork_id]);
		print_status(philo, FORK);
		pthread_mutex_lock(&forks[left_fork_id]);
		print_status(philo, FORK);
	}
}

static void	drop_forks(t_philo *philo, pthread_mutex_t *forks, int left_fork_id,
		int right_fork_id)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&forks[left_fork_id]);
		print_status(philo, DROP_FORKS);
		pthread_mutex_unlock(&forks[right_fork_id]);
		print_status(philo, DROP_FORKS);
	}
	else
	{
		pthread_mutex_unlock(&forks[right_fork_id]);
		print_status(philo, DROP_FORKS);
		pthread_mutex_unlock(&forks[left_fork_id]);
		print_status(philo, DROP_FORKS);
	}
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = get_table();
	take_forks(philo, table->forks, philo->left_fork_id, philo->right_fork_id);
	print_status(philo, EATING);
	philo->eat_count++;
	philo->last_meal = get_time();
	ft_usleep(table->time_to_eat);
	drop_forks(philo, table->forks, philo->left_fork_id, philo->right_fork_id);
	philo->status = SLEEPING;
}

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
