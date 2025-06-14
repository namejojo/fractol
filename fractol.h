/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:45:49 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/14 16:10:50 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef WIDTH
#  define HIGHT 1000
#  define WIDTH 1000
# endif

#include "my_libft/libft.h"
#include <math.h>

typedef struct s_comp
{
	double	real;
	double	i;
}	t_comp;

typedef struct s_image
{
	int		bpp;
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*pixel_ptr;
}	t_image;


typedef struct s_mlx_data
{
	int 	ac;
	double 	mult;
	double 	y;
	double 	x;
	double	i;
	double	real;
	void	*win_ptr;
	void	*win_ptr2;
	void	*mlx_ptr;
	t_image	img;
}	t_mlx_data;


int	Julia_Set(double z_real, double z_i, double c_real, double c_i);
int	Mandelbrot(double c_real, double c_i);
int	fractol_formula(double z_real, double z_i, double c_real, double c_i);

#endif
