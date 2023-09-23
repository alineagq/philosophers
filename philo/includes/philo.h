/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:08:09 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/23 18:52:41 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}					t_state;

typedef struct s_philo
{
	int				id;
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_count;
	long			last_meal;
	struct s_philo	*next;
}					t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	long			start_time;
	t_philo			*philos;
}					t_table;

int					ft_atoi(const char *str);
void				error(char *str, int exit_code);
int					ft_isdigit(int c);
int					str_is_digit(char *str);
void				get_table_info(void);
int					init_simulation(int argc, char **argv);
t_table				*get_table(void);
char				*ft_strchr(const char *s, int c);
t_philo				*get_philo(int id);
t_philo				*init_philo(int id);
long				get_time(void);

#endif