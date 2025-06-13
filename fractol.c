/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:39:16 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/13 15:48:21 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** xpm-read.c for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Tue Dec 11 15:25:27 2001 olivier crouzet
** Last update Sat Oct  1 14:40:55 2005 Olivier Crouzet
*/


#include "mlx_linux/mlx_int.h"
#include "mlx_linux/mlx.h"
#include "fractol.h"
#include <limits.h>

int encode_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void	my_pixel_put(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y / 4) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}

void	color_screen_Mandelbrot(t_mlx_data *data)
{
	float	x;
	float	y;

	y = 0;
	while (y++ < HIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, Mandelbrot((x / WIDTH) * 3 - 2.25, 1.5 - (y / HIGHT) * 3));
	}
}

void	color_screen_Julia_set(t_mlx_data *data)
{
	float	x;
	float	y;

	y = 0;
	while (y++ < HIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, Julia_Set((x / WIDTH) * 3 - 1.5, 1.5 - (y / HIGHT) * 3, data->real, data->i));
	}
}

int	loopers(int key, t_mlx_data *data)
{
	if (key == XK_Escape)
	{
		printf("were getting the fuck outta here\n\n");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		exit(1);
	}
	write (1, "loop\n", 5);
	return (key);
}

int keyboar_input(int key, t_mlx_data *data)
{
	if (key == XK_Escape || key == 1)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		exit(1);
	}
	if (key == XK_space)
	{
		if (data->ac < 2)
			color_screen_Mandelbrot(data);
		else
			color_screen_Julia_set(data);
	}
	return (0);
}

int	mouse_input(int mb, t_mlx_data *data)
{
	if (mb == 1)
		printf("left click\n");
	if (mb == 2)
		printf("midle click\n");
	if (mb == 3)
		printf("right click\n");
	if (mb == 4)
		printf("scroll up\n");
	if (mb == 5)
		printf("scroll down\n");
	if (mb == XK_Escape)
	{
		printf("were getting the fuck outta here\n\n");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);
		exit(1);
	}
	return (0);
}

int	Mandelbrot(float c_real, float c_i)
{
	t_comp		z;
	int			ind;
	float		real;

	z.real = 0;
	z.i = 0;
	ind = 0;
	while (ind++ < 42)
	{
		real = (z.real * z.real) - (z.i * z.i) + c_real;
		z.i = (z.real * z.i * 2) + c_i;
		z.real = real;
		if (z.real != z.real || z.i != z.i)
			return ((42 - ind) * (INT_MAX / 42));
	}
	return (0);
}

int	Julia_Set(float z_real, float z_i, float c_real, float c_i)
{
	int			ind;
	float		real;

	ind = 0;
	while (ind++ < 42)
	{
		real = (z_real * z_real) - (z_i * z_i) + c_real;
		z_i = (z_real * z_i * 2) + c_i;
		z_real = real;
		if (z_real != z_real || z_i != z_i)
			return ((42 - ind) * (INT_MAX / 42));
	}
	return (0);
}

int main(int ac, char **av)
{
	t_mlx_data	data;

	data.ac = 1;
	if (ac == 3)
	{
		data.ac = ac;
		data.real = atof (av[1]);
		data.i = atof (av[2]);
	}
	fflush(stdout);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HIGHT, "Hello_world!");
	if (data.win_ptr == NULL)
		return (mlx_destroy_display(data.mlx_ptr), free (data.mlx_ptr), 1);

	data.img.img_ptr = mlx_new_image(data.mlx_ptr, HIGHT, HIGHT);

	data.img.pixel_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);
	
	mlx_mouse_hook(data.win_ptr, mouse_input, &data);

	// mlx_key_hook(data.win_ptr, keyboar_input, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, keyboar_input, &data);
	
	// mlx_loop_hook(data.mlx_ptr, loopers, &data);
	
	mlx_loop(data.mlx_ptr);
	

	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free (data.mlx_ptr);
}
