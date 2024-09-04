/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:30:30 by phanta            #+#    #+#             */
/*   Updated: 2024/09/04 14:47:09 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void setplayer(char c, int y, int x)
{
    data()->posX=(double)x+0.5;
    data()->posY=(double)y+0.5;

    if(c=='N')
    {
        data()->dirX=0;
        data()->dirY=-1;
        data()->planeX=0.66;//not scalable, change
        data()->planeY=0;
    }
    if(c=='S')
    {
        data()->dirX=0;
        data()->dirY=1;
        data()->planeX=-0.66;
        data()->planeY=0;
    }
    if(c=='E')
    {
        data()->dirX=1;
        data()->dirY=0;
        data()->planeX=0;
        data()->planeY=0.66;
    }
    if(c=='W')
    {
        data()->dirX=-1;
        data()->dirY=0;
        data()->planeX=0;
        data()->planeY=-0.66;
    }
}

void drawRay(int x, int start, int end, unsigned long color)
{
    int i;

    i=-1;
    while(++i<start)
        my_mlx_pixel_put(&(data()->current_frame), x, i, 0x87CEEB);
    while(start<=end)
        my_mlx_pixel_put(&(data()->current_frame), x, start++, color);
    while(++end<RESH)
        my_mlx_pixel_put(&(data()->current_frame), x, end, 0x8ACE00);
}

void    raycastLoop()
{
	t_img	img;
	img.img = mlx_new_image(data()->mlx, RESW, RESH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    data()->current_frame=img;
    int x=-1;
    int stepX;
    int stepY;
    int mapX;
    int mapY;
    double deltaDistX;
    double deltaDistY;
    double rayDirX;
    double rayDirY;
	double		perpWallDist;
    
    int side;
    int hit;
    double sideDistX;
    double sideDistY;
    unsigned long color;
    
    while(++x<RESW)
    {
        hit=0;
        mapX = data()->posX;
        mapY = data()->posY;
        data()->cameraX=2*x/(double)(RESW-1)-1.0;
        
        rayDirX=data()->dirX+data()->planeX*data()->cameraX;
        rayDirY=data()->dirY+data()->planeY*data()->cameraX;
        //printf("raydirX=%f, raydirY=%f\n",rayDirX, rayDirY);
        //printf("---------x=%i--------rayDirX=%f, rayDirY=%f--------\n\n", x, rayDirX, rayDirY);
        if(rayDirX==0)
            deltaDistX=1e30;
        else
            deltaDistX = fabs(1.0 / rayDirX);
        if(rayDirY==0)
            deltaDistY=1e30;
        else
            deltaDistY = fabs(1.0 / rayDirY);
        if(rayDirX<0)
        {
            stepX=-1;
            sideDistX=(data()->posX-mapX)*deltaDistX;
        }
        else
        {
            stepX=1;
            sideDistX=(mapX+1.0-data()->posX)*deltaDistX;
        }
        if(rayDirY<0)
        {
            stepY=-1;
            sideDistY=(data()->posY-mapY)*deltaDistY;
        }
        else
        {
            stepY=1;
            sideDistY=(mapY + 1.0 - data()->posY) * deltaDistY;
        }
        
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //printf("sideDistX=%f, sideDistY=%f\n\n", sideDistX, sideDistY);
            //printf("MAP X=%i, MAP Y=%i, content=%c\n\n\n\n", mapX, mapY, data()->map->map[mapY][mapX]);
            if(check_borders(mapX, mapY) == '1')
                hit = 1;
        }
        if(side == 0)
            perpWallDist=(sideDistX-deltaDistX);
        else
            perpWallDist=(sideDistY-deltaDistY);
        int lineHeight;
        if(fabs(perpWallDist) < 1e-6)
            lineHeight=RESH;
        else
            lineHeight=(int)(RESH/perpWallDist);
        int drawStart=RESH/2-(lineHeight/2);
        if(drawStart<0)
            drawStart=0;
        int drawEnd=RESH/2+(lineHeight/2);
        if(drawEnd>RESH)
            drawEnd=RESH;
        if(side==0 && rayDirX<0)//E
            color=0xFFFF00;
        else if(side==0 && rayDirX>0)//W
            color=0x0000FF;
        else if(side==1 && rayDirY>0)//S
            color=0x00FF00;
        else if(side==1 && rayDirY<0)//N
            color=0xFF0000;
        else
            color=0xFFFFFF;
        //printf("side=%i, raydirX=%f, raydirY=%f\n",side, rayDirX, rayDirY);
        if (side == 0)
            color = (color & 0xfefefe) >> 1;
        //printf("PerpWallDist=%f, start=%i, end=%i, lineHeight=%i\n\n", perpWallDist, drawStart, drawEnd, lineHeight);
        drawRay(x, drawStart, drawEnd, color);
    }
    mlx_put_image_to_window(data()->mlx, data()->win, data()->current_frame.img, 0, 0);
    mlx_destroy_image(data()->mlx, data()->current_frame.img);
}

void calculus(char **map)//eu sei que aqui passei mas é para nao ter de estar a fazer data()->map->map[i][j] everytime lmao
{
    int i;
    int j;

    i=0;
    j=0;
    while(i<data()->map->height)
    {
        while(map[i][j])
        {
            if(map[i][j]=='N' ||map[i][j]=='S' ||map[i][j]=='E' ||map[i][j]=='W')//we can replace this by !isdigit se filtrarmos o mapa recebido para rejeitar outras letras
            {
                setplayer(map[i][j], i, j);
                printf("----------------------\ni=%i, j=%i\n---------------------------\n", i, j);
            }
            j++;
        }
        j=0;
        i++;
    }
    data()->time=timern();
    data()->oldTime=timern();
}
