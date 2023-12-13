#include "../../headers/cub3d.h"

/**
 * @brief Déterminez la direction du mur frappé par le rayon.
 *
 * La fonction `get_wall_direction` détermine la direction du mur frappé
 * par le rayon. Il assigne un code spécifique à `wall_dir` selon que
 * le rayon frappe un mur dans la direction nord, sud, est ou ouest.
 * Ces informations sont utiles pour le map de texture et le rendu correct des murs.
 *
 * @param m Pointeur vers la structure 't_MapConfig' contenant les données de la carte du jeu
 * @param c Pointeur vers la structure 't_CameraConfig' contenant les données de
 * configuration de la caméra.
 */
void	get_wall_direction(t_MapConfig *m, t_CameraConfig *c)
{
	if (c->hit && m->matrix[c->map_y][c->map_x] == '9')
		c->wall_dir = 9;
	else if (c->side == 1)
	{
		if (c->raydir_y < 0)
			c->wall_dir = 1;
		else
			c->wall_dir = 2;
	}
	else
	{
		if (c->raydir_x < 0)
			c->wall_dir = 3;
		else
			c->wall_dir = 4;
	}
}

/**
 * @brief Calculez la hauteur et les paramètres de rendu d'un segment de mur.
 *
 * La fonction `calculate_wall_height' est chargée de déterminer la hauteur d'un
 * segment de mur sur l'écran et de configurer les paramètres de rendu pour ce segment.
 * Cette fonction calcule la distance perpendiculaire au mur `perp_wd` en fonction
 * de la vue de la caméra et de la distance au mur. Il calcule ensuite la `line_height`
 * qui représente la hauteur du mur sur l'écran. Les valeurs `draw_start` et `draw_end`
 * sont définies pour spécifier où le segment de mur doit être dessiné dans l'espace
 * vertical de l'écran.
 *
 * @param cam Pointeur vers la structure 't_CameraConfig' contenantcontenant
 * les données de configuration de la caméra.
 */
void	calculate_wall_height(t_CameraConfig *cam)
{
	if (cam->side == 0)
		cam->perp_wd = (cam->s_dist_x - cam->ddist_x);
	else
		cam->perp_wd = (cam->s_dist_y - cam->ddist_y);
	if (cam->perp_wd)
		cam->line_height = (int)(WINDOW_Y / cam->perp_wd);
	else
		cam->line_height = WINDOW_Y;
	cam->draw_start = -cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + WINDOW_Y / 2;
	if (cam->draw_end >= WINDOW_Y)
		cam->draw_end = WINDOW_Y - 1;
}

/**
 * @brief Appliquez l'algorithme de l'Analyseur différentiel numérique
 * (Digital Differential Analyzer DDA) pour trouver le premier mur touché.
 *
 * La fonction `apply_dda` applique l'algorithme de l'Analyseur Différentiel
 * Numérique (DDA) pour tracer un rayon et trouver le point où il croise pour
 * la première fois un mur sur la carte du jeu. Il calcule de manière itérative
 * les distances horizontales et verticales jusqu'au prochain coup de mur potentiel
 * `s_dist_x` et `s_dist_y` et met à jour la position actuelle de la carte 
 * (`map_x` et `map_y') ainsi que la direction du pas du rayon `step_x` 
 * et `step_y`. La variable `side` est définie sur 0 pour les résultats horizontaux
 * et 1 pour les résultats verticaux.
 *
 * @param cam Pointeur vers la structure 't_CameraConfig' contenant les données
 * de configuration de la caméra.
 * @param m Pointeur vers la structure 't_MapConfig' contenant les données de
 * la carte du jeu.
 */
void	apply_dda(t_CameraConfig *cam, t_MapConfig *m)
{
	while (!cam->hit)
	{
		if (cam->s_dist_x < cam->s_dist_y)
		{
			cam->s_dist_x += cam->ddist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		}
		else
		{
			cam->s_dist_y += cam->ddist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (m->matrix[cam->map_y][cam->map_x] == '1'
			|| m->matrix[cam->map_y][cam->map_x] == '9')
			cam->hit = 1;
	}
}

/**
 * Calculez les valeurs de pas et de distance latérale initiale pour le lancer de rayons.
 *
 * Cette fonction calcule les valeurs de pas (`step_x` et `step_y`) pour le lancer de rayons
 * et initialise les valeurs de distance latérale (`s_dist_x` et `s_dist_y`) en fonction de
 * la direction du rayon de la caméra (`raydir_x` et `raydir_y`) et de la position du joueur.
 * Il détermine si le rayon se déplace vers la gauche ou la droite dans la direction X et
 * vers le haut ou vers le bas dans la direction Y et définit les valeurs de pas et de distance
 * latérale en conséquence.
 *
 * @param cam Un pointeur sur la structure de configuration de la caméra.
 * @param p Un pointeur vers la structure PlayerConfig représentant la position du joueur.
 */
void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p)
{
	cam->hit = 0;
	if (cam->raydir_x < 0)
	{
		cam->step_x = -1;
		cam->s_dist_x = (p->pos_x - cam->map_x) * cam->ddist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->s_dist_x = (cam->map_x + 1.0 - p->pos_x) * cam->ddist_x;
	}
	if (cam->raydir_y < 0)
	{
		cam->step_y = -1;
		cam->s_dist_y = (p->pos_y - cam->map_y) * cam->ddist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->s_dist_y = (cam->map_y + 1.0 - p->pos_y) * cam->ddist_y;
	}
}
