#include "../../headers/cub3d.h"

/**
 * @brief Dessine un cube statique sur l'image de la minimap.
 *
 * La fonction `draw_static_cube` dessine un carré d'un `type` (color)
 * sur l'image de la minimap aux coordonnées données.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 * @param type le type (color) du cube à dessiner.
 */
void	draw_static_cube(t_Cub3d *cub, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->draw_x + j),
				(cub->minimap->draw_y + i), type);
			j++;
		}
		i++;
	}
}

/**
 * @brief Dessine la position statique du joueur sur l'image de la minimap.
 *
 * La fonction `draw_static_player` marque la position du joueur sur l'image
 * de la minimap sous la forme d'un carré rouge. Il utilise les coordonnées du
 * joueur pour déterminer la position à dessiner.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 */
void	draw_static_player(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 13)
	{
		j = 0;
		while (j < 13)
		{
			my_mlx_pixel_put(cub->minimap->img, (cub->minimap->player_x + j),
				(cub->minimap->player_y + i), RED);
			j++;
		}
		i++;
	}
}

/**
 * @brief Dessinez la grille de carte statique sur l'image de la minimap.
 *
 * La fonction `draw_static_map` dessine une représentation statique de la
 * carte du jeu sur l'image de la minimap. Il parcourt la matrice de la carte
 * et dessine des cubes de différentes couleurs en fonction des éléments de
 * la carte (murs, espace vide, etc.).
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 */
void	draw_static_map(t_Cub3d *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (x < cub->map->max_line_len - 1)
		{
			if (ft_strchr("1", cub->map->matrix[y][x]))
				draw_static_cube(cub, GREY);
			else if (ft_strchr("0NSEW", cub->map->matrix[y][x]))
				draw_static_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 13;
		}
		cub->minimap->draw_y += 13;
		cub->minimap->draw_x = 0;
		y++;
	}
}
