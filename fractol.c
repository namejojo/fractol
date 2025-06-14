/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:39:16 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/14 17:01:11 by jlima-so         ###   ########.fr       */
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

void	free_all_fun(t_mlx_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->win_ptr2)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr2);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->mlx_ptr)
		free (data->mlx_ptr);
	exit (1);
}

void	set_data(t_mlx_data *data)
{
	data->ac = 1;
	data->real = 0;
	data->i = 0;
	data->x = 1.5;
	data->y = 1.5;
	data->mult = 3;
}

void	my_pixel_put(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}

void	color_screen_Mandelbrot(t_mlx_data *data)
{
	double	x;
	double	y;

	y = 0;
	while (y++ < HIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
				my_pixel_put(&data->img, x, y, 
				fractol_formula(0, 0, (x / WIDTH) * data->mult - (data->x + 0.75),
				data->y - (y / HIGHT) * data->mult));
	}
}

void	color_screen_Julia_set(t_mlx_data *data)
{
	double	x;
	double	y;

	y = 0;
	while (y++ < HIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
				my_pixel_put(&data->img, x, y, 
				fractol_formula((x / WIDTH) * data->mult - data->x,
				data->y - (y / HIGHT) * data->mult,
				data->real,
				data->i));
	}
}

// int	Mandelbrot(double c_real, double c_i)
// {
// 	t_comp		z;
// 	int			ind;
// 	double		real;

// 	z.real = 0;
// 	z.i = 0;
// 	ind = 0;
// 	while (ind++ < 150)
// 	{
// 		real = (z.real * z.real) - (z.i * z.i) + c_real;
// 		z.i = (z.real * z.i * 2) + c_i;
// 		z.real = real;
// 		if (z.real != z.real || z.i != z.i)
// 			return (color_code(ind));
// 	}
// 	return (0);
// }

int	color_code(float t)
{
	int	r;
	int	g;
	int	b;
	
	t = (t / 42);
	r = 9 * (1 - t) * t * t * t * 255;
	g = 15 * (1 - t) * (1 - t) * t * t * 255;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r + g + b);
}

int	fractol_formula(double z_real, double z_i, double c_real, double c_i)
{
	int			ind;
	double		real;

	ind = 0;
	while (ind++ < 42)
	{
		real = (z_real * z_real) - (z_i * z_i) + c_real;
		z_i = (z_real * z_i * 2) + c_i;
		z_real = real;
		if ((z_real * z_real) + (z_i * z_i) > 4)
			return (color_code(ind));
	}
	return (0);
}

void edit_data(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Left)
		data->x += data->mult / 10;
	if (keysym == XK_Right)
		data->x -= data->mult / 10;
	if (keysym == XK_Up)
		data->y += data->mult / 10;
	if (keysym == XK_Down)
		data->y -= data->mult / 10;
	if (keysym == XK_KP_Add)
	{
		data->x -= data->mult / 20;
		data->y -= data->mult / 20;
		data->mult -= data->mult / 10;
	}
	if (keysym == XK_KP_Subtract)
	{
		data->x += data->mult / 20;
		data->y += data->mult / 20;
		data->mult += data->mult / 10;
	}
}


int	key_hook(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		free_all_fun(data);
	if (keysym == XK_space)
	{
		set_data(data);
		if (data->ac == 1)
			color_screen_Mandelbrot(data);
		else
			color_screen_Julia_set(data);
	}
	edit_data(keysym, data);
	if (data->ac == 1)
		color_screen_Mandelbrot(data);
	else
		color_screen_Julia_set(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

void	color_second_screen_Julia_set(t_mlx_data *data, float real, float i)
{
	double	x;
	double	y;

	y = 0;
	while (y++ < HIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
				my_pixel_put(&data->img, x, y, 
				fractol_formula((x / WIDTH) * 3.3 - 1.65,
				1.65 - (y / HIGHT) * 3.3,
				real,
				i));
	}
}

int mouse_hook(int keysym, int x, int y,t_mlx_data *data)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	if (keysym == 1 && data->ac == 1)
	{
		if (data->win_ptr2 == NULL)
			data->win_ptr2 = mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "JULIA");
		if (data->win_ptr2 == NULL)
			free_all_fun(data);
		if (data->ac == 1)
			color_second_screen_Julia_set(data, (rx / WIDTH) * data->mult - (data->x + 0.75), data->y - (ry / HIGHT) * data->mult);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr2, data->img.img_ptr, 0, 0);
		printf("%f %f\n", (rx / WIDTH) * data->mult - (data->x + 0.75), data->y - (ry / HIGHT) * data->mult);
		fflush(stdout);
		return (0);
	}
	if (keysym == 2)
		write(1, "midle click\n", 13);
	if (keysym == 3)
	{
		data->ac = 3;
		data->real = (rx / WIDTH) * data->mult - (data->x + 0.75);
		data->i = data->y - (ry / HIGHT) * data->mult;
	}
	if (keysym == 4)
	{
		data->x -= (data->mult / 10) * (rx / WIDTH);
		data->y -= (data->mult / 10) * (ry / HIGHT);
		data->mult -= data->mult / 10;
	}
	if (keysym == 5)
	{
		data->x += (data->mult / 10) * (rx / WIDTH);
		data->y += (data->mult / 10) * (ry / HIGHT);
		data->mult += data->mult / 10;
	}
	if (data->ac == 1)
		color_screen_Mandelbrot(data);
	else
		color_screen_Julia_set(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	set_data(&data);
	if (ac == 3)
	{
		data.ac = ac;
		data.real = atof (av[1]);
		data.i = atof (av[2]);
	}
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr2 = NULL;
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HIGHT, "fractol");
	if (data.win_ptr == NULL)
		return (mlx_destroy_display(data.mlx_ptr), free (data.mlx_ptr), 1);
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HIGHT);
	data.img.pixel_ptr = mlx_get_data_addr
	(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, mouse_hook, &data);
	fflush(stdout);
	if (data.ac == 1)
		color_screen_Mandelbrot(&data);
	else
		color_screen_Julia_set(&data);
	mlx_loop(data.mlx_ptr);
}


// data.ac = 1;
// // data.real = 0;
// data.i = 0;
// data.x = 1.5;
// data.y = 1.5;
// data.mult = 3;