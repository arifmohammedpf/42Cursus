/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:53:48 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 11:20:27 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_rules *rules)
{
	int	i;

	i = rules->nb_of_philo;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_of_philo;
		rules->philosophers[i].rules = rules;
	}
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_of_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->print_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eat_all_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->death_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_mutex), NULL))
		return (1);
	return (0);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->is_all_ate = 0;
	rules->is_dead = 0;
	if (rules->nb_of_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->nb_of_philo > 250)
		return (1);
	if (argv[5])
	{
		rules->nb_to_eat = ft_atoi(argv[5]);
		if (rules->nb_to_eat <= 0)
			return (1);
	}
	else
		rules->nb_to_eat = -1;
	if (init_mutex(rules))
		return (2);
	init_philo(rules);
	return (0);
}

void	clear_all(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_of_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_of_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->print_mutex));
	pthread_mutex_destroy(&(rules->eat_all_mutex));
	pthread_mutex_destroy(&(rules->death_mutex));
	pthread_mutex_destroy(&(rules->meal_mutex));
}
