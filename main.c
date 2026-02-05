/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 01:16:38 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/05 20:51:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		put_error("Invalid input\nUsage: ./miniRT path/to/[scene].rt");
		return (1);
	}
	if (!initialize_scene(argv[1], &data.scene))
		return (clean_scene(&data.scene), 1);
	if (!initialize_window(&data.mlx, WIN_WIDTH, WIN_HEIGHT))
		return (clean_scene(&data.scene), 1);
	mlx_key_hook(data.mlx.win, handle_keypress, &data);
	mlx_hook(data.mlx.win, 17, 0, handle_close, &data);
	tracer_loop(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.win, data.mlx.img, 0, 0);
	mlx_loop(data.mlx.mlx);
	return (destroy_window(&data.mlx), clean_scene(&data.scene), 0);
}
