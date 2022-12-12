/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   poet.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 06:09:09 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 18:37:26 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	add_queue(unsigned long time, t_msg_type type, int id, t_deep *thoughts)
{
	t_log	*log;

	log = thoughts->log;
	pthread_mutex_lock(&thoughts->writers_block);
	if (log->queue_size < 0)
	{
		pthread_mutex_unlock(&thoughts->writers_block);
		return ;
	}
	log->queue[log->queue_size].type = type;
	log->queue[log->queue_size].time = time;
	log->queue[log->queue_size].id = id;
	log->queue_size++;
	if (log->queue_size > log->max)
	{
		printf("LOG OVERFLOW! Too many philos, or TT_EAT/TT_SLEEP too small!\n");
		printf("Printing of log will stop, but the simulation will run on.\n");
		log->queue_size = -200;
	}
	pthread_mutex_unlock(&thoughts->writers_block);
}

//change to print
static void	print_queue(t_deep *thoughts)
{
	t_log	*log;
	int		i;

	i = -1;
	log = thoughts->log;
	while (++i < log->print_size)
	{
		if (log->print[i].type == EAT && FOOD)
			printf(FORMAT_EAT, log->print[i].time, log->print[i].id,
				log->msgs[log->print[i].type], random_food(log));
		else
			printf(FORMAT_MSG, log->print[i].time, log->print[i].id,
				log->msgs[log->print[i].type]);
		if (log->print[i].type == DIE)
		{
			pthread_mutex_lock(&thoughts->writers_block);
			log->queue_size = -2000;
			pthread_mutex_unlock(&thoughts->writers_block);
			log->print_size = -2000;
			return ;
		}
	}
	log->print_size -= i;
}

static void	swap_print_queue(t_log *log)
{
	t_msg	*tmp;
	int		tmp_size;

	tmp = log->queue;
	tmp_size = log->queue_size;
	log->queue = log->print;
	log->queue_size = log->print_size;
	log->print = tmp;
	log->print_size = tmp_size;
}

void	*shakespeare(void *param)
{
	t_deep	*thoughts;
	t_log	*log;
	bool	existance;

	thoughts = param;
	existance = true;
	log = thoughts->log;
	while (existance)
	{
		existance = confirm_reality(thoughts);
		usleep (500);
		pthread_mutex_lock(&thoughts->writers_block);
		swap_print_queue(log);
		if (log->print_size > 0 || log->queue_size > 0)
			existance = true;
		if (log->print_size < 0 || log->queue_size < 0)
			existance = false;
		pthread_mutex_unlock(&thoughts->writers_block);
		print_queue(thoughts);
	}
	return (NULL);
}
