/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:45:49 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/13 14:06:33 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef WIDTH
#  define HIGHT 1000
#  define WIDTH 1000
# endif


#include "my_libft/libft.h"

typedef struct s_comp
{
	float	real;
	float	i;
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
	float	i;
	float	real;
	void	*win_ptr;
	void	*mlx_ptr;
	int 	ac;
	t_image	img;
}	t_mlx_data;


int	Julia_Set(float z_real, float z_i, float c_real, float c_i);
int	Mandelbrot(float c_real, float c_i);

#endif