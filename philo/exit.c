/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egolboyu <egolboyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:45:52 by egolboyu          #+#    #+#             */
/*   Updated: 2024/09/20 12:30:15 by egolboyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_no);
}

int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, details, 0));
}

void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}
