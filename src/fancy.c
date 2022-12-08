/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fancy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:43:37 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 20:11:00 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"



const char	*random_food(t_log *log)
{
	log->food_index++;
	if (log->food_index > FOOD_TYPES)
		log->food_index = 0;
	return (log->foods[log->food_index]);
}

static void	init_morefood(t_log *log)
{
	log->foods[20] = LUFFY;
	log->foods[21] = FRENCH;
	log->foods[22] = CURRY;
	log->foods[23] = SALAD;
	log->foods[24] = SUSHI;
	log->foods[25] = AVOCA;
	log->foods[26] = MANGO;
	log->foods[27] = CHERRY;
	log->foods[28] = DONUT;
	log->foods[29] = PANCAKE;
	log->foods[30] = APPLE2;
	log->foods[31] = KIWI;
	log->foods[32] = CHEESE;
	log->foods[33] = SHEPPIE;
	log->foods[34] = PEACHES;
	log->foods[35] = WATERM;
	log->foods[36] = EGG;
	log->foods[37] = COCONUT;
	log->foods[38] = CARROT;
	log->foods[39] = SHRIMP;
	log->foods[40] = CAKE;
}

void	init_fancy(t_log *log)
{
	log->foods[0] = SPAGHETTI;
	log->foods[1] = PIZZA;
	log->foods[2] = PIZZA_PEP;
	log->foods[3] = PIZZA_HAW;
	log->foods[4] = GRAPE;
	log->foods[5] = APPLE;
	log->foods[6] = IC_VAN;
	log->foods[7] = IC_CHOC;
	log->foods[8] = IC_COODOU;
	log->foods[9] = IC_STRAW;
	log->foods[10] = IC_BANANA;
	log->foods[11] = IC_RASP;
	log->foods[12] = BENTO;
	log->foods[13] = BURRITO;
	log->foods[14] = TACO;
	log->foods[15] = FALAFEL;
	log->foods[16] = SANDWICH;
	log->foods[17] = FRIES;
	log->foods[18] = HAMBURG;
	log->foods[19] = HOTDOGS;
	init_morefood(log);
}
