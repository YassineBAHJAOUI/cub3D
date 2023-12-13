#include "../../headers/cub3d.h"

static void	rotate_player_keys(t_Cub3d *cub, int dir)
{
	t_PlayerConfig	*p;
	t_CameraConfig	*c;
	t_Transform		rot_dir;
	t_Transform		rot_plane;
	double			angle;

	angle = 0.1;
	if (!dir)
		angle = -0.1;
	c = cub->cam;
	p = cub->player;
	rot_dir.x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	rot_dir.y = p->dir_x * sin(angle) + p->dir_y * cos(angle);
	p->dir_x = rot_dir.x;
	p->dir_y = rot_dir.y;
	rot_plane.x = c->plane_x * cos(angle) - c->plane_y * sin(angle);
	rot_plane.y = c->plane_x * sin(angle) + c->plane_y * cos(angle);
	c->plane_x = rot_plane.x;
	c->plane_y = rot_plane.y;
}

/**
 * @brief Vérification des collisions murales et mise à jour de la position
 * du joueur en conséquence.
 *
 * La fonction `check_wall_hit` examine la nouvelle position potentielle
 * du joueur (spécifiée par 'temp_x' et 'temp_y'` et vérifie si elle entre
 * en collision avec un mur de la carte du jeu. Si une collision est détectée,
 * la position du joueur est mise à jour aux coordonnées spécifiées, empêchant
 * le joueur de se déplacer à travers les murs.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param temp_x La coordonnée X temporaire de la position du joueur.
 * @param temp_y La coordonnée Y temporaire de la position du joueur.
 */
void	check_wall_hit(t_Cub3d *cub, double temp_x, double temp_y)
{
	t_MapConfig		*m;
	t_PlayerConfig	*p;

	m = cub->map;
	p = cub->player;
	if (m->matrix[(int)p->pos_y][(int)p->pos_x] == '1'
		|| m->matrix[(int)p->pos_y][(int)p->pos_x] == '9')
	{
		p->pos_y = temp_y;
		p->pos_x = temp_x;
	}
}

/**
 * @brief Applique un mouvement vers l'avant ou vers l'arrière au joueur.
 *
 * La fonction `apply_for_back_move` calcule la position du nouveau joueur
 * lorsqu'il avance ou recule (spécifiée par le paramètre `dir`) dans sa
 * direction actuelle. Il met à jour les coordonnées X et Y du joueur en
 * fonction de la direction, du vecteur de direction et d'une distance de
 * déplacement fixe. La fonction appelle ensuite 'check_wall_hit' pour
 * détecter et gérer les collisions avec les murs.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param p Pointeur vers la structure 't_PlayerConfig' contenant
 * les données de configuration du lecteur.
 * @param dir La direction du mouvement (1 pour l'avant, -1 pour l'arrière).
 */
void	apply_for_back_move(t_Cub3d *cub, t_PlayerConfig *p, int dir)
{
	double	temp_x;
	double	temp_y;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	p->pos_x += 0.2 * p->dir_x * dir;
	p->pos_y += 0.2 * p->dir_y * dir;
	check_wall_hit(cub, temp_x, temp_y);
}

/**
 * @brief Appliquez un mouvement à gauche ou à droite au joueur.
 *
 * La fonction `apply_left_right_move` calcule la position du nouveau
 * joueur lorsqu'il mitraille à gauche ou à droite (spécifiée par le paramètre
 * `dir`) par rapport à sa direction actuelle. Il met à jour les coordonnées X
 * et Y du joueur en fonction de la direction, du vecteur de direction
 * et d'une distance de déplacement fixe. La fonction appelle ensuite `check_wall_hit`
 * pour détecter et gérer les collisions avec les murs.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param p Pointeur vers la structure 't_PlayerConfig' contenant les données
 * de configuration du lecteur.
 * @param dir La direction du mouvement de mitraillage (1 pour la droite, -1 pour la gauche).
 */
void	apply_left_right_move(t_Cub3d *cub, t_PlayerConfig *p, int dir)
{
	double	temp_x;
	double	temp_y;

	temp_x = p->pos_x;
	temp_y = p->pos_y;
	if (dir)
	{
		p->pos_x += p->dir_y * 0.2;
		p->pos_y += -p->dir_x * 0.2;
	}
	else
	{
		p->pos_x += -p->dir_y * 0.2;
		p->pos_y += p->dir_x * 0.2;
	}
	check_wall_hit(cub, temp_x, temp_y);
}

/**
 * @brief Mouvement du joueur de poignée, à la fois avec la saisie au clavier
 * et le contrôle de la vue à la souris.
 *
 * La fonction `readmove` gère les mouvements des joueurs dans le monde du jeu.
 * Il vérifie l'état des touches de déplacement (haut, bas, gauche, droite) et
 * applique la logique de déplacement correspondante à l'aide des fonctions 
 * `apply_for_back_move` et `apply_left_right_move`. Ces fonctions calculent
 * la nouvelle position du joueur en fonction de la direction et de la distance
 * spécifiées par les touches de déplacement.
 * La fonction `on_mouse_move` est également appelée pour gérer le contrôle de
 * vue basé sur la souris. Si des touches de mouvement sont enfoncées ou s'il
 * y a un mouvement de la souris, la fonction renvoie 0 pour indiquer un mouvement
 * réussi; sinon, il renvoie 1 pour indiquer aucun mouvement.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param p Pointeur vers la structure 't_PlayerConfig' contenant les données
 * de configuration du lecteur.
 * @return Renvoie 0 si la position du joueur est mise à jour en raison d'un
 * mouvement ou d'un contrôle de vue, ou 1 si aucune touche de mouvement n'est
 * enfoncée et qu'il n'y a pas de mouvement de la souris.
 */
int	readmove(t_Cub3d *cub, t_PlayerConfig *p)
{
	if (p->up)
		apply_for_back_move(cub, p, 1);
	if (p->down)
		apply_for_back_move(cub, p, -1);
	if (p->left)
		apply_left_right_move(cub, p, 1);
	if (p->right)
		apply_left_right_move(cub, p, 0);
	if (p->l_key)
		rotate_player_keys(cub, 0);
	if (p->r_key)
		rotate_player_keys(cub, 1);
	on_mouse_move(cub);
	return (0);
}