/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:14:30 by maghumya          #+#    #+#             */
/*   Updated: 2026/02/05 20:51:34 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	put_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(message, 2);
	if (errno != 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		errno = 0;
	}
	ft_putendl_fd("", 2);
	return (false);
}

bool	parse_rgb(char *str, t_rgb *color)
{
	char	**components;

	components = ft_split(str, ',');
	if (!check_arg_format(components, 3, check_integer))
	{
		ft_free_array((void ***)&components);
		return (put_error("Invalid RGB format"));
	}
	color->r = ft_atoi(components[0]);
	color->g = ft_atoi(components[1]);
	color->b = ft_atoi(components[2]);
	if (!check_rgb_values(color->r, color->g, color->b))
	{
		ft_free_array((void ***)&components);
		return (put_error("Invalid RGB"));
	}
	ft_free_array((void ***)&components);
	return (true);
}

bool	parse_vec3(char *str, t_vec3 *vec)
{
	char	**components;

	components = ft_split(str, ',');
	if (!check_arg_format(components, 3, check_double))
	{
		ft_free_array((void ***)&components);
		return (put_error("Invalid vec3 format"));
	}
	vec->x = ft_atod(components[0]);
	vec->y = ft_atod(components[1]);
	vec->z = ft_atod(components[2]);
	ft_free_array((void ***)&components);
	return (true);
}
