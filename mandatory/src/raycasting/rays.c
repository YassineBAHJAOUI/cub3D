#include "../../headers/cub3d.h"

/**
 * @brief Crée une nouvelle image pour la fenêtre du jeu Cub3D.
 *
 * La fonction `cub3d_new_image` est responsable de la création d'un nouveau tampon
 * d'image pour la fenêtre du jeu Cub3D. Elle commence par détruire l'image existante
 * si une existe déjà, puis alloue une nouvelle image avec des dimensions spécifiées par
 * les constantes de taille de la fenêtre (WINDOW_X et WINDOW_Y). Elle met également à jour
 * l'adresse de l'image, le nombre de bits par pixel (bpp), la longueur de la ligne (len),
 * et l'ordre des octets (endian) pour la nouvelle image.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	cub3d_new_image(t_Cub3d *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr, &cub->img->bpp,
			&cub->img->len, &cub->img->endian);
}

/**
 * @brief Obtient la couleur d'un pixel à une position spécifiée dans une image.
 *
 * La fonction `my_mlx_pixel_get` récupère la couleur d'un pixel situé à la position
 * spécifiée `(x, y)` dans une image représentée par la structure `img`. Elle calcule
 * le décalage mémoire en fonction de l'adresse de l'image, de sa longueur et du nombre
 * de bits par pixel, puis renvoie la couleur sous forme d'entier non signé.
 *
 * @param img Pointeur vers la structure `t_ImageControl` représentant l'image.
 * @param x La position horizontale (colonne) du pixel.
 * @param y La position verticale (ligne) du pixel.
 * @return La couleur du pixel à la position `(x, y)` sous forme d'entier non signé.
 */
int	my_mlx_pixel_get(t_ImageControl *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->len) + \
	(x * img->bpp / 8))));
}

/**
 * @brief Initialise les propriétés d'un rayon pour une colonne spécifique de l'écran.
 *
 * La fonction `init_rays` initialise les propriétés d'un rayon pour une colonne
 * spécifique de l'écran pendant le processus de raycasting. Elle calcule la
 * position de la caméra sur l'écran (`camera_x`), la direction du rayon (`raydir_x`
 * et `raydir_y`), et la position initiale sur la carte (`map_x` et `map_y`).
 * De plus, elle calcule la distance delta (`ddist_x` et `ddist_y`)
 * nécessaire pour passer d'une cellule de grille à la suivante dans les directions
 * horizontale et verticale.
 *
 * @param cub Pointeur vers la structure `t_Cub3d` contenant le contexte du programme
 * et les données.
 * @param cam Pointeur vers la structure `t_CameraConfig` contenant la configuration de
 * la caméra.
 * @param x La colonne actuelle de l'écran en cours de traitement.
 */
void	init_rays(t_Cub3d *cub, t_CameraConfig *cam, int x)
{
	cam->camera_x = 2 * x / (double)WINDOW_X - 1;
	cam->raydir_x = cub->player->dir_x + cam->plane_x * cam->camera_x;
	cam->raydir_y = cub->player->dir_y + cam->plane_y * cam->camera_x;
	cam->map_x = floor(cub->player->pos_x);
	cam->map_y = floor(cub->player->pos_y);
	if (!cam->raydir_x)
		cam->ddist_x = 1e30;
	else
		cam->ddist_x = fabs(1 / cam->raydir_x);
	if (!cam->raydir_y)
		cam->ddist_y = 1e30;
	else
		cam->ddist_y = fabs(1 / cam->raydir_y);
}

/**
 * @brief Dessine la scène en lançant des rayons depuis la caméra pour chaque colonne de l'écran.
 *
 * La fonction `draw_rays` est responsable du rendu de la scène 3D en lançant
 * des rayons depuis la perspective de la caméra pour chaque colonne de l'écran.
 * Elle itère sur toutes les colonnes, initialise les propriétés du rayon, effectue
 * le lancer de rayons, calcule les hauteurs des murs, détermine les directions des
 * murs, et applique des textures pour rendre les murs. De plus, elle rend le plafond
 * et le sol avant de traiter chaque colonne.
 *
 * @param cub Pointeur vers la structure `t_Cub3d` contenant le contexte et les données du programme.
 */
void	draw_rays(t_Cub3d *cub)
{
	int				x;
	t_CameraConfig	*cam;

	cam = cub->cam;
	x = 0;
	cam_utils_init(cam);
	render_ceilling_floor(cub);
	while (x < WINDOW_X)
	{
		init_rays(cub, cam, x);
		step_calculation(cam, cub->player);
		apply_dda(cam, cub->map);
		calculate_wall_height(cam);
		get_wall_direction(cub->map, cub->cam);
		apply_texture(cub, cub->cam, x, cam->wall_dir);
		x++;
	}
}
