/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:03:12 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 12:11:45 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_rules *rules)
{
	int	result;

	pthread_mutex_lock(&(rules->death_mutex));
	result = rules->is_dead;
	pthread_mutex_unlock(&(rules->death_mutex));
	return (result);
}

int	check_if_all_ate(t_rules *rules)
{
	int	result;

	pthread_mutex_lock(&(rules->eat_all_mutex));
	result = rules->is_all_ate;
	pthread_mutex_unlock(&(rules->eat_all_mutex));
	return (result);
}

int	check_if_ate_enough(t_rules *rules, t_philosopher *philo)
{
	int	result;

	if (rules->nb_to_eat == -1)
		return (0);
	pthread_mutex_lock(&(rules->meal_mutex));
	result = (philo->x_ate >= rules->nb_to_eat);
	pthread_mutex_unlock(&(rules->meal_mutex));
	return (result);
}

void	*routine(void *void_philosopher)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!check_if_dead(rules))
	{
		if (!check_if_ate_enough(rules, philo))
			philo_eats(philo);
		else
			break ;
		if (check_if_all_ate(rules) || check_if_dead(rules))
			break ;
		print_philo_info(rules, philo->id, "is sleeping");
		philo_sleep(rules->time_to_sleep, rules);
		if (check_if_dead(rules))
			break ;
		print_philo_info(rules, philo->id, "is thinking");
		usleep(500);
	}
	return (NULL);
}

int	check_all_philos_ate(t_rules *rules)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < rules->nb_of_philo && all_ate)
	{
		pthread_mutex_lock(&(rules->meal_mutex));
		if (rules->philosophers[i].x_ate < rules->nb_to_eat)
			all_ate = 0;
		pthread_mutex_unlock(&(rules->meal_mutex));
		i++;
	}
	return (all_ate);
}
