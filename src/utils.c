/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 06:53:35 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 17:53:58 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	better_sleep(unsigned long duration)
{
	unsigned long	goal;
	unsigned long	now;
	unsigned long	delta;

	goal = get_time() + duration;
	while (true)
	{
		now = get_time();
		if (now >= goal)
			return ;
		delta = goal - now;
		if (delta <= 1)
		{
			while (get_time() < goal)
				usleep(200);
			return ;
		}
		usleep((delta * 2) / 3);
	}
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief Allocates a block of memory of count * size, and sets it all to NULL 
 * 
 * @param count Number of elements to allocate for.
 * @param size 	Size of the elements.
 * @return void* of count * size on success. NULL on fail.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	i = -1;
	while (++i < (count * size))
		((char *)mem)[i] = '\0';
	return (mem);
}

/**
 * @brief Turns a string into a long.
 * 
 * @param nb the string to be converted.
 * @return @b [long] 
 */
long	ft_atol(const char *nb)
{
	long			i;
	unsigned long	r;
	long			sign;

	i = 0;
	r = 0;
	sign = 1;
	while (nb[i] == ' ' || nb[i] == '\t' || nb[i] == '\v'
		|| nb[i] == '\f' || nb[i] == '\r' || nb[i] == '\n')
		i++;
	if (nb[i] == '-')
		sign = -1;
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		r = (r * 10) + (nb[i] - '0');
		i++;
	}
	return ((long)(r * sign));
}
