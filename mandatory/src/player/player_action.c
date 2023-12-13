#include "../../headers/cub3d.h"

/**
 * @brief Exécute une action d'utilisation dans le jeu.
 *
 * La fonction `use_action` calcule la position à laquelle le joueur a
 * l'intention d'effectuer une action d'utilisation en fonction de sa position
 * et de sa direction actuelles. Il vérifie si la tuile à la position calculée
 * sur la carte du jeu est un "9", représentant une porte. Si c'est le cas,
 * cela change la tuile en '0', indiquant que la porte a été utilisée. Sinon,
 * il renvoie une erreur pour signifier qu'aucune action n'a été effectuée.
 *
 * @ param p Pointeur vers la structure PlayerConfig contenant les informations sur le joueur.
 * @ param m Pointeur vers la structure MapConfig contenant les informations de la carte du jeu.
 * @ return 0 si l'action d'utilisation a réussi, 1 si aucune action n'a été effectuée.
 */
int	use_action(t_PlayerConfig *p, t_MapConfig *m)
{
	p->use_distance_x = p->pos_x + 0.7 * p->dir_x;
	p->use_distance_y = p->pos_y + 0.7 * p->dir_y;
	if (m->matrix[(int)p->use_distance_y][(int)p->use_distance_x] == '9')
		m->matrix[(int)p->use_distance_y][(int)p->use_distance_x] = '0';
	else
		return (1);
	return (0);
}

/**
 * @brief Animer le tir de l'arme du joueur.
 *
 * La fonction `shoot_gun` gère l'animation de tir de l'arme du joueur.
 * Il faut un compteur en entrée pour déterminer l'image d'animation actuelle.
 * En fonction de la valeur du compteur, il met à jour l'image du pistolet pour
 * afficher l'image correspondante de l'animation de tir. Lorsque l'animation est terminée,
 * elle réinitialise le compteur et restaure l'image par défaut du pistolet.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param p Pointeur vers la structure PlayerConfig contenant les informations sur le joueur.
 * @param counter Pointeur vers un compteur d'entiers pour les images d'animation.
 */
void	shoot_gun(t_Cub3d *cub, t_PlayerConfig *p, int *counter)
{
	if (*counter)
		mlx_destroy_image(cub->mlx_ptr, p->gun->img->img_ptr);
	if (*counter == 1)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_01.xpm");
	else if (*counter == 2)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_02.xpm");
	else if (*counter == 3)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_03.xpm");
	else if (*counter == 4)
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_04.xpm");
	else if (*counter == 5)
	{
		setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_00.xpm");
		p->shoot = 0;
		*counter = 0;
	}
}