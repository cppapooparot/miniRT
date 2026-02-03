/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:11:45 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/24 18:27:21 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb	result;

	result = (t_rgb){0, 0, 0};
	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	return (rgb_clamp(result));
}

t_rgb	rgb_scale(t_rgb color, double scalar)
{
	t_rgb	result;

	result = (t_rgb){0, 0, 0};
	result.r = (int)(color.r * scalar);
	result.g = (int)(color.g * scalar);
	result.b = (int)(color.b * scalar);
	return (rgb_clamp(result));
}

t_rgb	rgb_multiply(t_rgb a, t_rgb b)
{
	t_rgb	result;

	result = (t_rgb){0, 0, 0};
	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (rgb_clamp(result));
}

t_rgb	rgb_clamp(t_rgb color)
{
	if (color.r < 0)
		color.r = 0;
	else if (color.r > 255)
		color.r = 255;
	if (color.g < 0)
		color.g = 0;
	else if (color.g > 255)
		color.g = 255;
	if (color.b < 0)
		color.b = 0;
	else if (color.b > 255)
		color.b = 255;
	return (color);
}

int	rgb_to_int(t_rgb color)
{
	t_rgb	clamped;

	clamped = rgb_clamp(color);
	return ((clamped.r << 16) | (clamped.g << 8) | clamped.b);
}
