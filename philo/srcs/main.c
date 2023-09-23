/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:07:36 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 17:52:59 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_args(int argc, char **argv)
{
	int	i;
	int	num;

	if (argc < 5 || argc > 6)
		error("❌ - Wrong number of arguments.\n", EXIT_FAILURE);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		error("🔮 - You need at least one Philosopher.\n", EXIT_FAILURE);
	i = 2;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (str_is_digit(argv[i]))
			error("❌ - Arguments must be numbers.\n", EXIT_FAILURE);
		else if (ft_atoi(argv[i]) < 0)
			error("⏰ - You can't go back in time!\n", EXIT_FAILURE);
		else if (!ft_atoi(argv[i]) || ft_atoi(argv[i]) == 0)
			error("🌱 - No one knows the beginning of everything.\n",
				EXIT_FAILURE);
		i++;
	}
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	if (init_simulation(argc, argv))
		return (EXIT_FAILURE);
	// run_simulation();
	// clear_exit();
	return (EXIT_SUCCESS);
}
