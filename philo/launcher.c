/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:53:58 by arimoham          #+#    #+#             */
/*   Updated: 2025/03/14 12:07:08 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_meals(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	if (rules->nb_to_eat == -1)
		return (NULL);
	while (!check_if_dead(rules))
	{
		if (check_all_philos_ate(rules))
		{
			pthread_mutex_lock(&(rules->eat_all_mutex));
			rules->is_all_ate = 1;
			pthread_mutex_unlock(&(rules->eat_all_mutex));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_philosopher_death(t_rules *rules, int philo_id)
{
	long long	time;
	int			is_dead;

	is_dead = 0;
	pthread_mutex_lock(&(rules->meal_mutex));
	time = time_diff(rules->philosophers[philo_id].t_last_meal, timestamp());
	pthread_mutex_unlock(&(rules->meal_mutex));
	if (time > rules->time_to_die)
	{
		print_philo_info(rules, philo_id, "died");
		pthread_mutex_lock(&(rules->death_mutex));
		rules->is_dead = 1;
		pthread_mutex_unlock(&(rules->death_mutex));
		is_dead = 1;
	}
	return (is_dead);
}

void	*monitor_death(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (!check_if_all_ate(rules))
	{
		i = 0;
		while (i < rules->nb_of_philo)
		{
			if (check_philosopher_death(rules, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	create_philosophers(t_rules *rules, t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philo)
	{
		pthread_mutex_lock(&(rules->meal_mutex));
		p[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_mutex));
		if (pthread_create(&(p[i].thread_id), NULL, routine, &(p[i])))
			return (1);
		i++;
	}
	return (0);
}

int	launcher(t_rules *rules)
{
	t_philosopher	*p;
	pthread_t		death_monitor;
	pthread_t		meal_monitor;

	p = rules->philosophers;
	rules->first_timestamp = timestamp();
	if (create_philosophers(rules, p))
		return (1);
	if (pthread_create(&death_monitor, NULL, monitor_death, rules))
		return (1);
	if (pthread_create(&meal_monitor, NULL, monitor_meals, rules))
		return (1);
	pthread_join(death_monitor, NULL);
	pthread_join(meal_monitor, NULL);
	clear_all(rules, p);
	return (0);
}
