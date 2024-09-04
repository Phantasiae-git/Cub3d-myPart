/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:04:42 by phanta            #+#    #+#             */
/*   Updated: 2024/09/04 17:07:31 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"


int close_win()
{
    //frees e whatever
    exit(0);
}
void    do_walk()
{
    data()->sideDirX=data()->dirX;
    data()->sideDirY=data()->dirY;
    rotate_vector(&(data()->sideDirX), &(data()->sideDirY), 1.5708);
    
    if(data()->w==1)//forward
    {
        if(data()->map->map[(int)(data()->posY)][(int)(data()->posX + data()->dirX * data()->moveSpeed)] !='1')
            data()->posX += data()->dirX * data()->moveSpeed;
        if(data()->map->map[(int)(data()->posY + data()->dirY * data()->moveSpeed)][(int)(data()->posX)] !='1')
            data()->posY+= data()->dirY * data()->moveSpeed;
    }
    if(data()->a==1)//left
    {
        if(data()->map->map[(int)(data()->posY)][(int)(data()->posX - data()->sideDirX * data()->moveSpeed)] !='1')//add check_borders here too?
            data()->posX -= data()->sideDirX * data()->moveSpeed;
        if(data()->map->map[(int)(data()->posY - data()->sideDirY * data()->moveSpeed)][(int)(data()->posX)] !='1')
            data()->posY-= data()->sideDirY * data()->moveSpeed;
    }
    if(data()->s==1)//back
    {
        if(data()->map->map[(int)(data()->posY)][(int)(data()->posX - data()->dirX * data()->moveSpeed)] !='1')
            data()->posX -= data()->dirX * data()->moveSpeed;
        if(data()->map->map[(int)(data()->posY - data()->dirY * data()->moveSpeed)][(int)(data()->posX)]!='1')
            data()->posY-= data()->dirY * data()->moveSpeed;
    }
    if(data()->d==1)//right
    {
        if(data()->map->map[(int)(data()->posY)][(int)(data()->posX + data()->sideDirX * data()->moveSpeed)] !='1')
            data()->posX += data()->sideDirX * data()->moveSpeed;
        if(data()->map->map[(int)(data()->posY + data()->sideDirY * data()->moveSpeed)][(int)(data()->posX)]!='1')
            data()->posY+= data()->sideDirY * data()->moveSpeed;
    }
}

int walk(int keycode)
{  
    if(keycode==119)
        data()->w=1;
    if(keycode==97)
        data()->a=1;
    if(keycode==115)
        data()->s=1;
    if(keycode==100)
        data()->d=1;
    if(keycode==65307)
        close_win();
    if(keycode==65361)
        data()->rotation--;
    if(keycode==65363)
        data()->rotation++;
    //printf("keycode=%i\n", keycode);
    //printf("keycode:%c, w:%i, a:%i, s:%i, d:%i\n", keycode, data()->w,data()->a,data()->s,data()->d);
    return(0);
}

int stop(int keycode)
{
    if(keycode==119)
        data()->w=0;
    if(keycode==97)
        data()->a=0;
    if(keycode==115)
        data()->s=0;
    if(keycode==100)
        data()->d=0;
    if(keycode==65361)
        data()->rotation++;
    if(keycode==65363)
        data()->rotation--;
    return(0);
}
