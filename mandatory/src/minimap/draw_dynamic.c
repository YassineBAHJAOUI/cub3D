#include "../../headers/cub3d.h"

/**
 * @brief Dessinez un cube dynamique sur l'image de la minimap.
 *
 * La fonction `draw_dynamic_cube` dessine un carré d'un `type` (color)
 * sur l'image de la minimap à la position de dessin actuelle. Il est
 * utilisé pour représenter des objets dynamiques sur la minimap.
 *
 * @param cub Pointeur vers la structure jeu Cub3D.
 * @param type le type (color) du cube à dessiner.
 */
void	draw_dynamic_cube(t_Cub3d *cub, int type)
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
 * @brief Dessinez la carte dynamique sur l'image de la minimap.
 *
 * La fonction `draw_dynamic_map` dessine une partie dynamique de la carte du jeu
 * sur l'image de la minimap. Il considère la position du joueur et dessine une partie
 * de la carte autour du joueur, jusqu'à 11x11 tuiles, avec différentes couleurs en fonction
 * des éléments de la carte (murs, espace vide, etc.). Cette fonction est utilisée pour
 * fournir une représentation dynamique du monde du jeu sur la minimap.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 * @param temp_x Variable temporaire pour le calcul de la position horizontale.
 * @param temp_y Variable temporaire pour le calcul de la position verticale.
 */
void	draw_dynamic_map(t_Cub3d *cub, int temp_x, int temp_y)
{
	int	x;
	int	y;

	y = (int)cub->player->pos_y - 5;
	temp_y = y;
	while (y < (temp_y + 11))
	{
		x = (int)cub->player->pos_x - 5;
		temp_x = x;
		while (x < (temp_x + 11))
		{
			if (y >= cub->map->n_lines + 1 || y < 0
				|| x >= max_x_array(cub) || x < 0)
				draw_dynamic_cube(cub, BLACK);
			else if (ft_strchr("19 ", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, GREY);
			else if (ft_strchr("0NSWE", cub->map->matrix[y][x]))
				draw_dynamic_cube(cub, WHITE);
			x++;
			cub->minimap->draw_x += 13;
		}
		cub->minimap->draw_y += 13;
		cub->minimap->draw_x = 0;
		y++;
	}
}

/**
 * @brief Dessine la position dynamique du joueur sur l'image de la minimap.
 *
 * La fonction `draw_dynamic_player` marque la position du joueur sur l'image de
 * la minimap sous la forme d'un carré rouge. Il utilise une position fixe par rapport
 * à la zone de la minimap pour dessiner la représentation du joueur. Cette fonction
 * fournit un indicateur dynamique de l'emplacement du joueur sur la minimap.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 */
void	draw_dynamic_player(t_Cub3d *cub)
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
			my_mlx_pixel_put(cub->minimap->img, ((13 * 5) + j),
				((13 * 5) + i), RED);
			j++;
		}
		i++;
	}
}
