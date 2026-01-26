/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:43:08 by maghumya          #+#    #+#             */
/*   Updated: 2026/01/26 15:56:15 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../libft/libft.h"

bool	check_arg_format(char **tokens, int len,
		bool (*check_func)(const char *))
{
	int	index;

	if (!check_split_length(tokens, len))
		return (false);
	index = -1;
	while (++index < len)
		if (!check_func(tokens[index]))
			return (false);
	return (true);
}

bool	check_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

bool	check_ranged(double value, double min, double max)
{
	if (value < min || value > max)
		return (false);
	return (true);
}

bool	check_range_vec3(t_vec3 vec, double min, double max)
{
	if (!check_ranged(vec.x, min, max))
		return (false);
	if (!check_ranged(vec.y, min, max))
		return (false);
	if (!check_ranged(vec.z, min, max))
		return (false);
	return (true);
}
