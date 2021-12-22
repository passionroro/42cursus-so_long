/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:31:19 by rohoarau          #+#    #+#             */
/*   Updated: 2021/12/15 14:29:46 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 The aim of these functions is to display a new window with given textures 
 according to the .ber file given in parameters.
 There is also <key_command>, a function that registers the key strokes, and 
 <shutdown>, the function that closes the window.
 *
*/

void	ft_show_image(t_var *v)
{
	if (v->map[v->x][v->y] == '1')
		v->img = mlx_xpm_file_to_image(v->mlx, "includes/sep.xpm", &v->s, \
				&v->s);
	if (v->map[v->x][v->y] == '0')
		v->img = mlx_xpm_file_to_image(v->mlx, "includes/ground.xpm", &v->s, \
				&v->s);
	if (v->map[v->x][v->y] == 'C')
		v->img = mlx_xpm_file_to_image(v->mlx, "includes/oil.xpm", &v->s, \
				&v->s);
	if (v->map[v->x][v->y] == 'E')
	{
		v->img = mlx_xpm_file_to_image(v->mlx, "includes/exit_grey.xpm", \
				&v->s, &v->s);
		v->x_ext = v->x;
		v->y_ext = v->y;
	}
	if (v->map[v->x][v->y] == 'P')
	{
		v->img = mlx_xpm_file_to_image(v->mlx, "includes/biden-r.xpm", &v->s, \
				&v->s);
		v->x_pos = v->x;
		v->y_pos = v->y;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, v->y * v->s, v->x * v->s);
}

int	key_command(int keycode, t_var *vars)
{
	int	ret;

	ret = 0;
	if (keycode == 53)
		ft_free_map(vars, "[ESC]");
	if (keycode == 13)
		ret = move_up(vars, vars->x_pos - 1, vars->y_pos);
	if (keycode == 0)
		ret = move_left(vars, vars->x_pos, vars->y_pos - 1);
	if (keycode == 1)
		ret = move_down(vars, vars->x_pos + 1, vars->y_pos);
	if (keycode == 2)
		ret = move_right(vars, vars->x_pos, vars->y_pos + 1);
	if (ret == 2)
		ft_free_map(vars, "success!");
	return (0);
}

int	shutdown(int status, t_var *var)
{
	(void)var;
	(void)status;
	printf("Exit: [RED CROSS]\n");
	exit (0);
	return (0);
}

int	read_image(t_var v)
{
	v.x = 0;
	v.y = 0;
	v.mlx = mlx_init();
	v.img = mlx_xpm_file_to_image(v.mlx, "includes/ground.xpm", &v.s, &v.s);
	v.win = mlx_new_window(v.mlx, v.s * v.columns, v.s * v.lines, "$3.318");
	mlx_hook(v.win, 17, 1L << 19, shutdown, &v);
	mlx_hook(v.win, 2, 1L << 0, key_command, &v);
	while (v.x < v.lines)
	{
		printf("%s", v.map[v.x]);
		while (v.y < v.columns)
		{
			ft_show_image(&v);
			v.y++;
		}
		v.y = 0;
		v.x++;
	}
	mlx_loop(v.mlx);
	return (0);
}
