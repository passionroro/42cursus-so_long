/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:44:10 by rohoarau          #+#    #+#             */
/*   Updated: 2021/12/15 14:20:30 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 These functions are used to mak the plater move up, left, down and right using 
 the WASD commands.
 *	check_pos : player can't move if he's facing a wall or a grey exit.
 *	the player can exit only if he has collected all the collectibles.
*/

int	check_pos(t_var *vars, int x, int y)
{
	count_moves(vars);
	if (vars->map[x][y] == '1')
		return (1);
	if (vars->map[x][y] == 'C')
	{
		if (vars->collectible >= 0)
		{
			vars->map[x][y] = '0';
			vars->collectible -= 1;
		}
		if (vars->collectible == 0)
		{
			vars->img = mlx_xpm_file_to_image(vars->mlx, "includes/exit.xpm", \
					&vars->s, &vars->s);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img, \
					vars->y_ext * vars->s, vars->x_ext * vars->s);
		}
	}
	if (vars->map[x][y] == 'E')
	{
		if (vars->collectible == 0)
			return (2);
		return (1);
	}
	return (0);
}

int	move_up(t_var *v, int xx, int yy)
{
	int	ret;

	ret = check_pos(v, xx, yy);
	if (ret != 0)
		return (ret);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/biden-u.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, yy * v->s, \
			xx * v->s);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/ground.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, v->y_pos * v->s, \
			v->x_pos * v->s);
	v->x_pos -= 1;
	return (0);
}

int	move_down(t_var *v, int xx, int yy)
{
	int	ret;

	ret = check_pos(v, xx, yy);
	if (ret != 0)
		return (ret);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/biden-d.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, yy * v->s, \
			xx * v->s);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/ground.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, v->y_pos * v->s, \
			v->x_pos * v->s);
	v->x_pos += 1;
	return (0);
}

int	move_right(t_var *v, int xx, int yy)
{
	int	ret;

	ret = check_pos(v, xx, yy);
	if (ret != 0)
		return (ret);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/biden-r.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, yy * v->s, \
			xx * v->s);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/ground.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, v->y_pos * v->s, \
			v->x_pos * v->s);
	v->y_pos += 1;
	return (0);
}

int	move_left(t_var *v, int xx, int yy)
{
	int	ret;

	ret = check_pos(v, xx, yy);
	if (ret != 0)
		return (ret);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/biden-l.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, yy * v->s, \
			xx * v->s);
	v->img = mlx_xpm_file_to_image(v->mlx, "includes/ground.xpm", &v->s, \
			&v->s);
	mlx_put_image_to_window(v->mlx, v->win, v->img, v->y_pos * v->s, \
			v->x_pos * v->s);
	v->y_pos -= 1;
	return (0);
}
