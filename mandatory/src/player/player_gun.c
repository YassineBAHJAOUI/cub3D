#include "../../headers/cub3d.h"

/**
 * @brief Vérification de la tolérance de couleur pour la correspondance des couleurs des pixels.
 *
 * La fonction `check_tolerance` vérifie si une couleur de pixel donnée correspond à un niveau de tolérance
 * prédéfini pour les canaux de couleur (rouge, vert et bleu). Il est utilisé pour filtrer des couleurs
 * spécifiques ("p" pour le rose ou " b " pour le noir) d'une image.
 *
 * @param color La couleur du pixel à vérifier.
 * @param c Un caractère indiquant le filtre de couleur à appliquer ('p' pour le rose ou ' b ' pour le noir).
 * @return Renvoie 1 si la couleur réussit le contrôle de tolérance, 0 sinon.
 */
static int	check_tolerance(int color, char c)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (c == 'b')
	{
		if (abs(r - 0x00) > 120
			|| abs(g - 0x00) > 120
			|| abs(b - 0x00) > 120)
			return (0);
	}
	else if (c == 'p')
	{
		if (abs(r - 0xFF) > 120
			|| abs(g - 0) > 120
			|| abs(b - 0xFF) > 120)
			return (0);
	}
	return (1);
}

/**
 * @brief Dessinez l'arme du joueur sur l'écran de jeu.
 *
 * La fonction `draw_gun` est responsable du rendu de l'image du pistolet du joueur
 * sur l'écran de jeu avec filtrage des couleurs. Il extrait les couleurs des pixels
 * de l'image du pistolet, applique un filtre de couleur pour le rose ('p') et
 * restitue l'image filtrée.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param p Pointeur vers la structure PlayerConfig contenant les informations sur le joueur.
 * @param x La position horizontale de départ pour le rendu de l'image du pistolet.
 * @param y La position verticale de départ pour le rendu de l'image du pistolet.
 */
void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
{
	int	color;

	color = 0;
	x = 0;
	while (x < p->gun->img->width)
	{
		y = 0;
		while (y < p->gun->img->height)
		{
			color = my_mlx_pixel_get(p->gun->img, x, y);
			if (!check_tolerance(color, 'p'))
				my_mlx_pixel_put(cub->img, WINDOW_X - 760 + x,
					WINDOW_Y - 530 + y, color);
			y++;
		}
		x++;
	}
}

/**
 * @brief Dessine un crosshair sur l'écran de jeu.
 *
 * La fonction `draw_crosshair` affiche une image en croix sur l'écran de jeu avec filtrage
 * des couleurs. Il extrait les couleurs des pixels de l'image en croix, applique un filtre
 * de couleur pour le noir ("b") et restitue l'image filtrée au centre de l'écran de jeu.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param p Pointeur vers la structure PlayerConfig contenant les informations sur le joueur.
 * @param x La position horizontale de départ pour le rendu de l'image en croix.
 * @param y La position verticale de départ pour le rendu de l'image en croix.
 */
void	draw_crosshair(t_Cub3d *cub, t_PlayerConfig *p, int x, int y)
{
	int	color;

	color = 0;
	x = 0;
	while (x < p->crosshair->img->width)
	{
		y = 0;
		while (y < p->crosshair->img->height)
		{
			color = my_mlx_pixel_get(p->crosshair->img, x, y);
			if (!check_tolerance(color, 'b'))
				my_mlx_pixel_put(cub->img,
					(WINDOW_X / 2) - (p->crosshair->img->width / 2) + x,
					(WINDOW_Y / 2) - (p->crosshair->img->height / 2) + y,
					color);
			y++;
		}
		x++;
	}
}

/**
 * @brief Initialise le pistolet et le crosshair du joueur.
 *
 * La fonction `player_gun` initialise les images du pistolet et du crosshair du joueur en
 * allouant de la mémoire pour les configurations de texture et les contrôles d'image.
 * Il charge les images du pistolet et du crosshair à partir des chemins de fichiers et
 * configure les structures de données nécessaires.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param p Pointeur vers la structure PlayerConfig contenant les informations sur le joueur.
 * @return Renvoie 0 en cas d'initialisation réussie.
 */
int	player_gun(t_Cub3d *cub, t_PlayerConfig *p)
{
	p->gun = ft_calloc(1, sizeof(t_TextureSetup));
	(void)p->gun->path;
	p->gun->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, p->gun, "./sprites/Gun_Sprites/g_00.xpm");
	p->crosshair = ft_calloc(1, sizeof(t_TextureSetup));
	(void)p->crosshair->path;
	p->crosshair->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, p->crosshair, "./sprites/Gun_Sprites/crosshair.xpm");
	cub->gun_ok = true;
	return (0);
}