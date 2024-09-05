/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:30:30 by phanta            #+#    #+#             */
/*   Updated: 2024/09/05 15:37:53 by phanta           ###   ########.fr       */
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

void drawRay(int x, int start, int end, t_img tex, double wallX, int lineHeight)
{
    int i;
    unsigned int color; 
    double step;
    double texPos;
    int texY;
    int texX;
    texX = (int)(wallX * tex.x);
    //printf("height=%i, lineH=%i\n",tex.y, lineHeight);
    if(fabs(data()->perpWallDist) < 1e-6)
    {
        step=0;
        texPos=(double)tex.y/2.0;
    }
    else
    {
        step = (double)tex.y / (double)lineHeight;
        texPos= (start - RESH/ 2 + lineHeight / 2) * step;
    }
    //printf("texX=%i, step=%f, texPos=%f\n", texX, step, texPos); 
    i=-1;
    while(++i<start)
        my_mlx_pixel_put(&(data()->current_frame), x, i, 0x87CEEB);
    while(start<=end)
    {
        texY = (int)texPos % (tex.y - 1);
        texPos += step;
        color=get_color(&tex,texX, texY);
        //printf("x=%i, y=%i, texPos=%f\n", texX, texY, texPos); 
        my_mlx_pixel_put(&(data()->current_frame), x, start++, color);
    }
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
    
    int side;
    int hit;
    double sideDistX;
    double sideDistY;
    t_img tex;
    
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
            data()->perpWallDist=(sideDistX-deltaDistX);
        else
            data()->perpWallDist=(sideDistY-deltaDistY);
        int lineHeight;
        if(fabs(data()->perpWallDist) < 1e-6)
            lineHeight=RESH;
        else
            lineHeight=(int)(RESH/data()->perpWallDist);
        int drawStart=RESH/2-(lineHeight/2);
        if(drawStart<0)
            drawStart=0;
        int drawEnd=RESH/2+(lineHeight/2);
        if(drawEnd>RESH)
            drawEnd=RESH;
        double wallX; 
        if (side == 0) 
            wallX = data()->posY + data()->perpWallDist * rayDirY;
        else
            wallX = data()->posX + data()->perpWallDist * rayDirX;
        wallX -= floor((wallX));
        if(side==0 && rayDirX<0)//E
            tex=data()->textures[0];
        else if(side==0 && rayDirX>0)//W
            tex=data()->textures[1];
        else if(side==1 && rayDirY>0)//S
            tex=data()->textures[2];
        else if(side==1 && rayDirY<0)//N
            tex=data()->textures[3];
        //printf("side=%i, raydirX=%f, raydirY=%f\n",side, rayDirX, rayDirY);
        // if (side == 0)
        //     color = (color & 0xfefefe) >> 1;
        //printf("data()->perpWallDist=%f, start=%i, end=%i, lineHeight=%i\n\n", data()->perpWallDist, drawStart, drawEnd, lineHeight);
        drawRay(x, drawStart, drawEnd, tex, wallX, lineHeight);
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
