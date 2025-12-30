/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:44:02 by maghumya          #+#    #+#             */
/*   Updated: 2025/12/30 16:02:55 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	check_file_extension(char *filename)
{
	int		len;
	char	*ext;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	ext = filename + len - 3;
	if (ft_strcmp(ext, ".rt") == 0)
		return (true);
	return (false);
}

bool	check_double(const char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
			str++;
	}
	if (*str != '\0' && *str != '\n')
		return (false);
	return (true);
}

bool	check_integer(const char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0' && *str != '\n')
		return (false);
	return (true);
}

bool	check_split_length(char **tokens, int expected_length)
{
	int count;

	count = 0;
	if (!tokens)
		return (false);
	while (tokens[count])
		count++;
	return (count == expected_length);
}