/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:46:27 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 14:58:58 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(int argc, char **argv)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	exit_status = init_table(argc, argv);
	if (!exit_status)
		exit_status = init_philosopher();
	get_table_info();
	return (exit_status);
}
