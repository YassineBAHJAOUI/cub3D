#include "../../headers/cub3d.h"

/**
 * @brief Définissez et stockez les paramètres de couleur du sol ou du plafond dans
 * les informations de map.
 *
 * Fonction utilitaire utilisée par 'put_floor_ceil_color' pour définir les paramètres
 * de couleur du sol ou du plafond dans la description de la scène. Il extrait et convertit
 * les composants de couleur RGB du tableau 'colors' fourni et définit l'entrée correspondante
 * dans le tableau 'floor_c' ou 'ceiling_c' de la structure 't_MapConfig' dans `t_Cub3d`
 * fourni.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param n Un entier indiquant s'il faut traiter la couleur du sol (0) ou du plafond (1).
 *  @param colors Tableau contenant des composants de couleur RGB.
 */
static	void	put_floor_ceil_color_utils(t_Cub3d *cub, int n, char **colors)
{
	if (n == 0)
	{
		cub->map->floor_c[ft_atoi(colors[0])]
		[ft_atoi(colors[1])]
		[ft_atoi(colors[2])] = 1;
	}
	else
	{
		cub->map->ceilling_c[ft_atoi(colors[0])]
		[ft_atoi(colors[1])]
		[ft_atoi(colors[2])] = 1;
	}
}

/**
 * @brief Définissez et stockez les paramètres de couleur du sol ou du plafond dans les informations de map.
 *
 * Cette fonction traite et stocke les paramètres de couleur du sol ou du plafond dans la description de la scène.
 * Il extrait et convertit les composants de couleur RGB à partir de la `ligne ' fournie, qui représente un paramètre
 * de couleur, et définit l'entrée correspondante dans le tableau `floor_c` ou `ceiling_c` de la structure `t_MapConfig`
 * dans `t_Cub3d` fourni. De plus, la fonction effectue une validation sur les composants de couleur fournis pour s'assurer
 * qu'ils se situent dans la plage valide de 0 à 255. Si un composant s'avère hors de portée,
 * la fonction termine le programme avec un message d'erreur.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param line Un pointeur sur la ligne courante contenant le paramètre de couleur.
 * @param n Un entier indiquant s'il faut traiter la couleur du sol (0) ou du plafond (1).
 * @param i Index pour itérer sur les composants de couleur.
 */
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i)
{
	char	**colors;

	colors = ft_split(line + 2, ',');
	while (i < 3)
	{
		if (!(ft_atoi(colors[i]) >= 0 && ft_atoi(colors[i]) <= 255))
		{
			free_main(cub);
			printf("Error: Invalid color range\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (n == 0)
		put_floor_ceil_color_utils(cub, 0, colors);
	else
		put_floor_ceil_color_utils(cub, 1, colors);
	ft_free_split(colors);
	cub->map->colors[n] = true;
}
