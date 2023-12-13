#include "../../headers/cub3d.h"

/**
 * @brief Rend la première image du jeu Cub3D.
 *
 * La fonction 'draw_first_frame' est responsable du rendu de l'image
 * initiale du jeu Cub3D. Il dessine la vue, la minimap, le pistolet
 * et le réticule du joueur sur la fenêtre de jeu. Cette fonction est
 * généralement appelée lorsque le jeu est démarré pour la première fois
 * ou après être revenu du menu principal pour afficher le monde du jeu au joueur.
 *
 * Pointeur @param cub vers la structure t_Cub3d .
 */
static void	draw_first_frame(t_Cub3d *cub)
{
	draw_rays(cub);
	draw_minimap(cub);
	draw_gun(cub, cub->player, 0, 0);
	draw_crosshair(cub, cub->player, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->minimap->img->img_ptr, 30, 30);
	cub->menu_active = false;
}

/**
 * @brief Gère les événements d'entrée de la souris dans le jeu Cub3D.
 *
 * La fonction 'mouse_hook' est appelée lorsqu'un événement d'entrée de souris
 * se produit dans la fenêtre de jeu Cub3D. Il gère les clics du bouton gauche
 * de la souris, vérifie si des boutons spécifiques du menu du jeu ont été cliqués
 * et déclenche des actions en conséquence. Si le menu du jeu est actif et que le
 * bouton "start" est cliqué, il affiche la première image du jeu.
 * Si le bouton "Quit" est cliqué, il ferme la fenêtre du jeu. Si le menu
 * n'est pas actif, il signale au joueur d'effectuer une action de tir.
 *
 * touche @ param Le bouton de la souris qui a été enfoncé.
 * @param x La coordonnée x du curseur de la souris.
 * @param y La coordonnée y du curseur de la souris.
 * Pointeur @ param cub vers la structure t_Cub3d représentant l'application Cub3D.
 * @return renvoie toujours 0 pour indiquer une gestion réussie de l'événement de la souris.
 */
int	mouse_hook(int key, int x, int y, t_Cub3d *cub)
{
	int	start;
	int	quit;

	(void)x;
	(void)y;
	start = 0;
	quit = 0;
	if (cub->menu_active && key == 1)
	{
		start = button_mo(cub, cub->main->start->img, 's');
		quit = button_mo(cub, cub->main->quit->img, 'q');
		if (start)
			draw_first_frame(cub);
		else if (quit)
			win_close(cub);
	}
	else
		cub->player->shoot = 1;
	return (0);
}

/**
 * @brief Fait pivoter la vue du joueur et la direction de la caméra en fonction d'un angle donné.
 *
 * La fonction 'rotate_player' calcule la nouvelle direction du joueur et du plan de la caméra
 * après avoir appliqué la rotation spécifiée par le paramètre 'angle'. Il met à jour la direction
 * du joueur et le plan de la caméra dans le contexte du jeu (`cub`) en conséquence.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param angle L'angle de rotation de la vue du joueur.
 */
static void	rotate_player(t_Cub3d *cub, double angle)
{
	t_PlayerConfig	*p;
	t_CameraConfig	*c;
	t_Transform		rot_dir;
	t_Transform		rot_plane;

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
 * @brief poignée mouvement de la souris et rotation de la caméra.
 *
 * La fonction 'on_mouse_move' est responsable de la mise à jour de l'orientation
 * de la caméra en fonction du mouvement de la souris. Il calcule le changement de
 * position de la souris ('mouse_x_diff'), gère le débordement de la souris sur
 * les bords de l'écran et ajuste la rotation de la caméra en conséquence.
 * Cette fonction garantit une rotation fluide et continue de la caméra même lorsque
 * le curseur de la souris atteint les limites de l'écran.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return 0 si la caméra est tournée, 1 s'il n'y a pas de mouvement de la souris.
 */
int	on_mouse_move(t_Cub3d *cub)
{
	int		temp_x;
	int		mouse_x_diff;
	int		overflow;

	temp_x = cub->mouse_x;
	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, &cub->mouse_x, &cub->mouse_y);
	mouse_x_diff = cub->mouse_x - temp_x;
	if (cub->mouse_x < 1)
	{
		overflow = -cub->mouse_x;
		cub->mouse_x = WINDOW_X - overflow;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, WINDOW_X - 1, cub->mouse_y);
	}
	else if (cub->mouse_x >= WINDOW_X - 1)
	{
		overflow = cub->mouse_x - (WINDOW_X - 1);
		cub->mouse_x = overflow;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, 0, cub->mouse_y);
	}
	if (mouse_x_diff)
		return (rotate_player(cub, 0.002 * mouse_x_diff), 0);
	return (1);
}