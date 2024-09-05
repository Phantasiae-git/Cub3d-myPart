/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:21:13 by phanta            #+#    #+#             */
/*   Updated: 2024/09/05 09:34:41 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void updates(void)
{
	double frameTime;
	data()->oldTime=data()->time;
    data()->time=timern();
	frameTime=(data()->time - data()->oldTime) / 1000.0;
	//static int a;
	// if(++a%2==0)i
	// {
	// 	printf("FPS:%f\n",(1.0 / frameTime));
	// 	mlx_string_put(data()->mlx, data()->win, 50, 50, 0x000000, ft_itoa((int)1.0/frameTime));
	// }
	data()->moveSpeed=frameTime*ROT_MULTIPLIER;
	data()->rotSpeed=frameTime*MOVE_SPEED_MULTIPLIER;  
}

int renderLoop(void)
{
	camera();
	do_rotate();
	do_walk();
    raycastLoop();
    updates();
	return(0);
}