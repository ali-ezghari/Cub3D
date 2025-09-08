/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:38:19 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/08 10:07:34 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	main(int argc, char *argv[])
{
	t_info			*data;
	struct s_game	game;

	data = malloc(sizeof(t_info));
	if (!data)
		return (1);
	ft_memset(data, 0, sizeof(t_info));
	parser(argc, argv[1], data);
	game.data = data;
	init_game(&game);
	init_mlx(&game);
	init_player(&game, &game.player);
	if (load_textures(&game) == 1)
		exit_error(1, "Failed to load one of the textures\n", game.data);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 0, handle_destroy, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (0);
}
