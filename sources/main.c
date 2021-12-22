/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:31:40 by rohoarau          #+#    #+#             */
/*   Updated: 2021/12/15 14:25:55 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		return (write(1, "Error\n", 6));
	if (argc == 2)
	{
		var.lines = ft_lines(argv[1]);
		var.columns = ft_columns(argv[1]);
		var.map = map_storage(argv[1], var);
		if (map_validity(&var) == 1)
			ft_free_map(&var, "Map error");
		read_image(var);
	}
	return (0);
}
