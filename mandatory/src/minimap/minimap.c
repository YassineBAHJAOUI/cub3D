#include "../../headers/cub3d.h"

/**
 * @brief Créez une nouvelle image pour la minimap et configurez ses propriétés.
 *
 * La fonction `minimap_new_image` détruit l'image de la minimap existante, crée une
 * nouvelle image avec les dimensions spécifiées (largeur et hauteur) et configure
 * son adresse et ses propriétés. Il réinitialise également la position de dessin
 * pour la minimap.
 *
 * Cette fonction est utilisée pour mettre à jour l'image de la minimap lorsque
 * la taille ou le contenu doit changer.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	minimap_new_image(t_Cub3d *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->minimap->img->img_ptr);
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
			cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &cub->minimap->img->bpp,
			&cub->minimap->img->len, &cub->minimap->img->endian);
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
}

/**
 * @brief Vérifiez et déterminez la hauteur de la minimap en fonction de la hauteur maximale autorisée.
 *
 * La fonction `check_minimap_size_height` calcule la hauteur de la minimap en fonction de la hauteur
 * maximale autorisée (max_height) tout en s'assurant qu'elle s'inscrit dans les contraintes spécifiées.
 * Si la taille de la minimap dépasse les contraintes, elle définit un indicateur indiquant que la minimap
 * doit être ajustée.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param max_height La hauteur maximale autorisée pour la minimap.
 * @return Renvoie La hauteur calculée de la minimap, en tenant compte des contraintes.
 */
static int	check_minimap_size_height(t_Cub3d *cub, int max_height)
{
	if (((cub->map->n_lines + 1) * 13) <= max_height)
		return (((cub->map->n_lines + 1) * 13));
	else
		return (cub->minimap->flag = 1, max_height);
}

/**
 * @brief Vérifiez et déterminez la largeur de la minimap en fonction de la
 * largeur maximale autorisée.
 *
 * La fonction `check_minimap_size_width` calcule la largeur de la minimap
 * en fonction de la largeur maximale autorisée (max_width) tout en veillant
 * à ce qu'elle respecte les contraintes spécifiées. Si la taille de la minimap
 * dépasse les contraintes, elle définit un indicateur indiquant que la
 * minimap doit être ajustée.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param max_width La largeur maximale autorisée pour la minimap.
 * @return Renvoie La largeur calculée de La minimap, en tenant compte des contraintes.
 */
static int	check_minimap_size_width(t_Cub3d *cub, int max_width)
{
	if ((max_x_array(cub) * 13) <= max_width)
		return ((max_x_array(cub) * 13));
	else
		return (cub->minimap->flag = 1, max_width);
}

/**
 * @brief Initialise la minimap, y compris ses dimensions et ses propriétés d'image.
 *
 * La fonction `init_minimap` initialise la minimap en allouant de la mémoire pour
 * la minimap et les structures de contrôle d'image. Il détermine la largeur et la
 * hauteur de la minimap en fonction des contraintes et définit l'adresse et les
 * propriétés de l'image. Si des ajustements sont nécessaires en raison de
 * contraintes, il définit un indicateur en conséquence.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	init_minimap(t_Cub3d *cub)
{
	cub->minimap = ft_calloc(1, sizeof(t_MiniMap));
	cub->minimap->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->minimap->width = check_minimap_size_width(cub, 143);
	cub->minimap->height = check_minimap_size_height(cub, 143);
	if (cub->minimap->flag == 1)
	{
		cub->minimap->width = 143;
		cub->minimap->height = 143;
	}
	cub->minimap->img->img_ptr = mlx_new_image(cub->mlx_ptr,
			cub->minimap->width, cub->minimap->height);
	cub->minimap->img->addr = mlx_get_data_addr(
			cub->minimap->img->img_ptr, &cub->minimap->img->bpp,
			&cub->minimap->img->len, &cub->minimap->img->endian);
	cub->minimap->draw_x = 0;
	cub->minimap->draw_y = 0;
	cub->minimap_ok = true;
}

/**
 * @brief Dessinez la minimap sur l'écran de jeu.
 *
 * La fonction `draw_minimap` est responsable du rendu de la minimap sur l'écran de jeu.
 * Il calcule la position du joueur sur la minimap et dessine soit la carte statique,
 * soit la carte dynamique en fonction du drapeau. Cette fonction joue un rôle essentiel
 * en fournissant au joueur une représentation visuelle du monde du jeu.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @return Renvoie une valeur entière indiquant le succès (0) du dessin de la minimap.
 */
int	draw_minimap(t_Cub3d *cub)
{
	cub->minimap->player_x = ((int)cub->player->pos_x) * 13;
	cub->minimap->player_y = ((int)cub->player->pos_y) * 13;
	if (cub->minimap->flag == 0)
	{
		draw_static_map(cub);
		draw_static_player(cub);
	}
	else
	{
		draw_dynamic_map(cub, 0, 0);
		draw_dynamic_player(cub);
	}
	return (0);
}
