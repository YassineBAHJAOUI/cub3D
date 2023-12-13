#include "../../headers/cub3d.h"

/**
 * @brief Définissez la direction du joueur et le plan de la caméra pour
 * l'orientation Nord ou Sud.
 *
 * La fonction `set_ns_direction` est responsable de la configuration de
 * la direction du joueur et du plan de la caméra en fonction de l'orientation
 * `i` fournie. Lorsque `i` est égal à 1, il définit la direction du joueur vers
 * le nord (vers le haut) et le plan de la caméra pour créer un champ de vision
 * vers la gauche. Lorsque `i` est égal à 2, il définit la direction du joueur
 * vers le sud (vers le bas) et le plan de la caméra pour créer un champ de vision
 * vers la droite.
 *
 * @param c Pointeur vers la structure 't_CameraConfig' contenant les données
 * de configuration de la caméra.
 * @param p Pointeur vers la structure 't_PlayerConfig' contenant les données
 * de configuration du lecteur.
 * @param i Un entier représentant l'orientation souhaitée (1 pour le Nord,
 * 2 pour le Sud).
 */
static void	set_ns_direction(t_CameraConfig *c, t_PlayerConfig *p, int i)
{
	if (i == 1)
	{
		p->dir_x = 0;
		p->dir_y = -1;
		c->plane_x = c->fov;
		c->plane_y = 0;
	}
	else if (i == 2)
	{
		p->dir_x = 0;
		p->dir_y = 1;
		c->plane_x = -c->fov;
		c->plane_y = 0;
	}
}

/**
 * @brief Définissez la direction du joueur et le plan de la caméra pour
 * l'orientation Ouest ou Est.
 *
 * La fonction `set_we_direction` est responsable de la configuration de la
 * direction du joueur et du plan de la caméra en fonction de l'orientation
 * `i` fournie. Lorsque `i` est égal à 3, il définit la direction du joueur
 * vers l'ouest (face à la gauche) et le plan de la caméra pour créer un champ
 * de vision vers le haut. Lorsque `i` est égal à 4, il définit la direction
 * du joueur vers l'Est (face à la droite) et le plan de la caméra pour créer
 * un champ de vision vers le bas.
 *
 * @param c Pointeur vers la structure 't_CameraConfig' contenant les données
 * de configuration de la caméra.
 * @param p Pointeur vers la structure 't_PlayerConfig' contenant les données
 * de configuration du lecteur.
 * @param i Un entier représentant l'orientation souhaitée (3 pour l'Ouest, 4 pour l'Est).
 */
static void	set_we_direction(t_CameraConfig *c, t_PlayerConfig *p, int i)
{
	if (i == 3)
	{
		p->dir_x = -1;
		p->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = -c->fov;
	}
	else if (i == 4)
	{
		p->dir_x = 1;
		p->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = c->fov;
	}
}

/**
 * @brief Initialise la configuration du joueur sur la carte.
 *
 * La fonction `player_init` est responsable de l'initialisation
 * de la configuration du joueur dans la carte. Il alloue de la mémoire
 * pour une structure 't_PlayerConfig' et définit la position initiale du
 * joueur sur (-1, -1) dans le contexte `t_Cub3d ' fourni. De plus,
 * le champ de vision du joueur (FOV) est défini sur un angle de champ de
 * vision horizontal par défaut et un angle de champ de vision vertical fixe.
 * 
 * Le programme appelle ensuite les fonctions `set_player_position` et `raycast_init`
 * pour configurer davantage la position du joueur et l'initialisation du lancer de
 * rayons. Si l'allocation de mémoire échoue, la fonction renvoie 1, indiquant un échec.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @return Renvoie 0 en cas de succès, ou 1 en cas d'échec d'allocation de mémoire.
 */
int	player_init(t_Cub3d *cub)
{
	cub->player = ft_calloc(1, sizeof(t_PlayerConfig));
	if (!cub->player)
		return (1);
	cub->player->pos_x = -1;
	cub->player->pos_y = -1;
	cub->player->orientation = 0;
	return (0);
}

/**
 * @brief Met à jour la position et la direction du joueur.
 *
 * La fonction `update_player` est responsable de la mise à jour de la position
 * et de l'orientation du joueur en fonction du personnage représentant le joueur
 * ('N', 'S', 'W' ou 'E') dans la carte du jeu. Il définit la direction et la position
 * du joueur en conséquence, en veillant à ce que le joueur soit correctement placé et
 * orienté dans le bon sens au début de la partie.
 *
 * @param cub Pointeur vers la structure du jeu Cub3D.
 * @param m Pointeur vers la structure MapConfig contenant les données de la carte du jeu.
 * @param i L'index de ligne indiquant la position verticale du joueur sur la carte.
 * @param j L'index de la colonne indiquant la position horizontale du joueur sur la carte.
 */
static void	update_player(t_Cub3d *cub, t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j] == 'N')
		set_ns_direction(cub->cam, cub->player, 1);
	else if (m->matrix[i][j] == 'S')
		set_ns_direction(cub->cam, cub->player, 2);
	else if (m->matrix[i][j] == 'W')
		set_we_direction(cub->cam, cub->player, 3);
	else if (m->matrix[i][j] == 'E')
		set_we_direction(cub->cam, cub->player, 4);
	cub->player->pos_y = i;
	cub->player->pos_x = j;
}

/**
 * @brief Définit la position initiale et la direction du joueur.
 *
 * La fonction `set_player_position` recherche sur la carte du jeu
 * une position de départ du joueur indiquée par les caractères
 * 'N', 'S', 'E' ou' W', représentant les directions cardinales
 * (Nord, Sud, Est, Ouest). Lorsqu'une position de départ valide
 * est trouvée, elle définit la position initiale et la direction
 * du joueur en conséquence. Cette fonction garantit que le joueur
 * est correctement placé dans le monde du jeu avant de commencer le jeu.
 *
 * @param cub Pointeur vers la structure 't_Cub3d' contenant le contexte
 * et les données du programme.
 */
void	set_player_position(t_Cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map->matrix[i])
	{
		j = 0;
		while (cub->map->matrix[i][j])
		{
			if (ft_strchr("NSEW", cub->map->matrix[i][j]))
			{
				update_player(cub, cub->map, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
