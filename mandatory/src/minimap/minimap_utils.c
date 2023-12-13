#include "../../headers/cub3d.h"

/**
 * @brief Trouvez la longueur maximale des lignes (nombre de colonnes) dans la matrice de la carte.
 *
 * La fonction `max_x_array` parcourt les lignes de la matrice de la carte et calcule la longueur
 * (nombre de colonnes) de chaque ligne. Il garde une trace de la longueur maximale des lignes rencontrées
 * lors de l'itération, fournissant la largeur maximale de la grille de la carte.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 * @return Renvoie la longueur maximale des lignes (nombre de colonnes) dans la matrice de la carte.
 */
int	max_x_array(t_Cub3d *cub)
{
	int	y;
	int	x;
	int	most_x;

	y = 0;
	x = 0;
	most_x = 0;
	while (y < cub->map->n_lines + 1)
	{
		x = 0;
		while (cub->map->matrix[y][x])
			x++;
		if (x > most_x)
			most_x = x;
		y++;
	}
	return (most_x);
}
