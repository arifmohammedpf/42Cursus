/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:54:13 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 12:09:56 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_rules
{
	int				nb_of_philo;
	int				nb_to_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				is_dead;
	int				is_all_ate;
	long long		first_timestamp;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_all_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philosopher	philosophers[250];
}	t_rules;

int			init_all(t_rules *rules, char **argv);

int			launcher(t_rules *rules);
void		*routine(void *void_philosopher);
void		clear_all(t_rules *rules, t_philosopher *philos);

int			ft_error(char *str);
int			print_error(int error);

int			ft_atoi(const char *str);
void		print_philo_info(t_rules *rules, int id, char *string);
void		philo_sleep(long long time, t_rules *rules);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);

int			check_if_dead(t_rules *rules);
int			check_if_all_ate(t_rules *rules);
int			check_all_philos_ate(t_rules *rules);
int			check_if_ate_enough(t_rules *rules, t_philosopher *philo);
void		monitor_philo_death(t_rules *rules);
void		monitor_philos_meals(t_rules *rules);
void		philo_eats(t_philosopher *philo);

#endif