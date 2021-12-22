/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:39:02 by rohoarau          #+#    #+#             */
/*   Updated: 2021/12/15 14:36:45 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 These functions have many purposes:
 *	storing the map in a 2D array (map_storage)
 *	checking if the map is valid
 *		it must be a rectangle (check_rectangle)
 *		it must only contain walls, ground, one player, one exit, and one or 
 		more collectibles
 *		the border should only be walls (check_char)
*/

char	**map_storage(char *path, t_var var)
{
	int		x;
	int		fd;
	char	**store;

	x = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit (0);
	store = (char **)malloc(sizeof(char *) * (var.lines + 1));
	if (!store)
		return (NULL);
	while (x < var.lines)
	{
		store[x] = malloc(sizeof(char) * (var.columns + 1));
		read(fd, store[x], (var.columns + 1));
		x++;
	}
	close(fd);
	return (store);
}

int	check_rectangle(t_var *var)
{
	static int	save_y;

	if (save_y == 0)
	{
		save_y = var->y;
		return (0);
	}
	if (save_y != var->y)
		return (1);
	if (var->y == var->lines)
		return (1);
	return (0);
}

int	check_char(t_var *var)
{
	if (var->map[0][var->y] != '1')
		return (1);
	if (var->map[var->lines - 1][var->y] != '1')
		return (1);
	if (var->map[var->x][0] != '1' )
		return (1);
	if (var->map[var->x][var->columns - 1] != '1')
		return (1);
	if (var->map[var->x][var->y] != '1' && var->map[var->x][var->y] != '0' \
			&& var->map[var->x][var->y] != 'E' \
			&& var->map[var->x][var->y] != 'C' \
			&& var->map[var->x][var->y] != 'P')
		return (1);
	if (var->map[var->x][var->y] == 'P')
		var->player++;
	if (var->map[var->x][var->y] == 'E')
		var->ext++;
	if (var->map[var->x][var->y] == 'C')
		var->collectible++;
	return (0);
}

int	map_validity(t_var *var)
{
	var->x = 0;
	var->y = 0;
	while (var->x < var->lines)
	{
		while (var->y < var->columns)
		{
			if (check_char(var) == 1)
				return (1);
			var->y++;
		}
		var->x++;
		if (check_rectangle(var) == 1)
			return (1);
		var->y = 0;
	}
	if (var->player != 1 || var->collectible == 0 || var->ext != 1)
		return (1);
	return (0);
}
