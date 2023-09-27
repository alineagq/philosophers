/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:08:09 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/26 22:23:23 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	DIED,
	THINKING,
	FORK,
	DROP_FORKS,
	EATING,
	SLEEPING,
}					t_status;

typedef struct s_philo
{
	int					id;
	_Atomic int			eat_count;
	_Atomic long long	last_meal;
	int					left_fork_id;
	int					right_fork_id;
	t_status			status;
	pthread_t			thread;
}					t_philo;

typedef struct table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	_Atomic int		num_eat;
	_Atomic int		any_philosopher_dead;
	_Atomic long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	died;
	pthread_mutex_t	data;
	pthread_mutex_t	print;
	t_philo			*philos;
}					t_table;

long				get_time(void);
char				*ft_strchr(const char *s, int c);
int					ft_isdigit(int c);
int					str_is_digit(char *str);
int					ft_atoi(const char *str);
void				error(char *str, int exit_code);
int					init_simulation(int argc, char **argv);
t_table				*get_table(void);
int					init_table(int argc, char **argv);
void				get_table_info(void);
int					init_philosopher(void);
void				print_status(t_philo *philo, int status);
void				run_simulation(void);
void				*routine(void *arg);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);
void				clean_simulation(void);
void				ft_usleep(long time);
int					all_philosophers_have_eaten(t_table *table);
int					one_philo_die(t_table *table, t_philo *philo);
int					keep_threads_alive(t_philo *philo);
void				thinking(t_philo *philo);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
#endif