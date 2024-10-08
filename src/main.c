/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phanta <phanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:14:17 by david             #+#    #+#             */
/*   Updated: 2024/09/05 12:28:40 by phanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void startGame()
{
	data()->mlx = mlx_init(); 
	data()->win = mlx_new_window(data()->mlx, RESW, RESH, "CADA 1 NO SEU QUADRADO");
	//mlx_mouse_hide(data()->mlx, data()->win);
	calculus(data()->map->map);
	data()->rotation=0;
	data()->textures=(t_img *)malloc(sizeof(t_img)*4);
	int i;
	i=-1;
	while(++i<4)
	{
		data()->textures[i].img=mlx_xpm_file_to_image(data()->mlx,"img/NO_OLIVES.xpm", &(data()->textures[i].x), &(data()->textures[i].y));
		data()->textures[i].addr=mlx_get_data_addr(data()->textures[i].img, &(data()->textures[i].bits_per_pixel), &(data()->textures[i].line_length), &(data()->textures[i].endian));
	}
	printf("%p, %i, %i, %i, %i\n",data()->textures[0].addr, data()->textures[0].x, data()->textures[0].y, data()->textures[0].bits_per_pixel, data()->textures[0].endian);
	mlx_loop_hook(data()->mlx,&renderLoop,NULL);
	mlx_hook(data()->win, 02, (1L<<0), walk, NULL);
	mlx_hook(data()->win, 03, (1L<<1), stop, NULL);
	mlx_hook(data()->win, 17, (1L<<2), close_win, NULL);
	mlx_loop(data()->mlx);
}

int main(int ac, char **av)
{
	// t_data	*game;

	// if (ac != 2)
	// 	error_handle(0, "wrong number of arguments\n", &game);
	// if (ft_strnstr(av[1] + ft_strlen(av[1]) - 4,
	// 	".cub", ft_strlen(av[1])) == NULL)
	// 	error_handle(0, "wrong file name\n", &game);
	// ft_memset(&game, 0, sizeof(t_data));
	// game = data();
	// if (ac == 2)
	// {
	// 	check_file(av[1], &game);
	// 	startGame();
	// 	//run game with all the calculus
	// }
	// return (0);
	(void)ac;
	getmatrix(av[1]);
	startGame();
}
