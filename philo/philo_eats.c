/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:53:20 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 14:23:54 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	acquire_forks(t_philosopher *philo, int first_fork, int second_fork)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[first_fork]));
	print_philo_info(rules, philo->id, "has taken a fork");
	if (rules->nb_of_philo == 1)
	{
		philo_sleep(rules->time_to_die * 2, rules);
		pthread_mutex_unlock(&(rules->forks[first_fork]));
		return ;
	}
	pthread_mutex_lock(&(rules->forks[second_fork]));
	print_philo_info(rules, philo->id, "has taken a fork");
}

void	eat_and_update(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	print_philo_info(rules, philo->id, "is eating");
	pthread_mutex_lock(&(rules->meal_mutex));
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_mutex));
	philo_sleep(rules->time_to_eat, rules);
	pthread_mutex_lock(&(rules->meal_mutex));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->meal_mutex));
}

void	release_forks(t_philosopher *philo, int first_fork, int second_fork)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_unlock(&(rules->forks[second_fork]));
	pthread_mutex_unlock(&(rules->forks[first_fork]));
}

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;
	int		first_fork;
	int		second_fork;

	rules = philo->rules;
	first_fork = philo->left_fork_id;
	second_fork = philo->right_fork_id;
	if (philo->left_fork_id > philo->right_fork_id)
	{
		first_fork = philo->right_fork_id;
		second_fork = philo->left_fork_id;
	}
	acquire_forks(philo, first_fork, second_fork);
	if (rules->nb_of_philo == 1)
		return ;
	eat_and_update(philo);
	release_forks(philo, first_fork, second_fork);
}
