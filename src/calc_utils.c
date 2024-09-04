/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:08:10 by phanta            #+#    #+#             */
/*   Updated: 2024/09/04 09:46:20 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	timern(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (0);
	return ((int)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

char    check_borders(int mapX, int mapY)
{
    //printf("mapY=%i, mapX=%i\n", mapY, mapX);
    if(mapY<0 || mapX<0 ||mapY>=data()->map->height|| mapX>=(int)ft_strlen(data()->map->map[mapY]))
        return('1');
    return(data()->map->map[mapY][mapX]);
}
