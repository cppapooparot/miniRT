/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:24:56 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/27 14:02:08 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "../mlx/mlx.h"
# include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_mlx;

bool					initialize_window(t_mlx *mlx, int width, int height);
void					destroy_window(t_mlx *mlx);
void					mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int						handle_keypress(int keycode, t_data *data);
int						handle_close(t_data *data);

#endif