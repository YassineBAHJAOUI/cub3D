#include "../../headers/cub3d.h"

/**
 * @brief Met à jour l'apparence d'un bouton en fonction de l'interaction de la souris.
 *
 * La fonction update_button modifie l'apparence d'un bouton en fonction des interactions
 * de la souris. Si le pointeur de la souris survole le bouton et que le paramètre 'p'
 * est différent de zéro, l'apparence du bouton est mise à jour à l'état "pressé".
 * Si 'p' est égal à zéro et que la souris ne survole pas le bouton, l'apparence du
 * bouton est mise à jour à l'état "non pressé".
 *
 * @param c Pointeur vers la structure t_Cub3d, représentant le contexte du jeu.
 * @param i Pointe vers la structure de contrôle t_Image représentant l'image du bouton.
 * @param p Non nul si le bouton est enfoncé, zéro sinon.
 * @param b Un identifiant de caractère pour le bouton ("s" pour démarrer, " q " pour quitter).
 */
void	update_button(t_Cub3d *c, t_ImageControl *i, int p, char b)
{
	mlx_destroy_image(c->mlx_ptr, i->img_ptr);
	if (b == 's')
	{
		if (p)
			setup_menu(c, c->main->start, "./sprites/Menu/start_01.xpm");
		else
			setup_menu(c, c->main->start, "./sprites/Menu/start_00.xpm");
		mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, i->img_ptr,
			(WINDOW_X / 2) - i->width / 2, ((WINDOW_Y - 100) / 2) - i->height);
	}
	else if (b == 'q')
	{
		if (p)
			setup_menu(c, c->main->quit, "./sprites/Menu/quit_01.xpm");
		else
			setup_menu(c, c->main->quit, "./sprites/Menu/quit_00.xpm");
		mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, i->img_ptr,
			(WINDOW_X / 2) - i->width / 2, ((WINDOW_Y + 450) / 2) - i->height);
	}
}

/**
 * @brief Vérifie si le pointeur de la souris est positionné sur l'image d'un bouton.
 *
 * La fonction button_mo vérifie si le pointeur de la souris est positionné sur l'image
 * d'un bouton. Il renvoie 1 si le pointeur de la souris est sur le bouton, et 0 sinon.
 *
 * @param cub Pointeur vers la structure t_Cub3d, représentant le contexte du jeu.
 * @param i pointe vers la structure de contrôle t_Image représentant l'image du bouton.
 * @param b Un identifiant de caractère pour le bouton ("s" pour démarrer, " q " pour quitter).
 * @return 1 si le pointeur de la souris est sur le bouton, 0 sinon.
 */
int	button_mo(t_Cub3d *cub, t_ImageControl *i, char b)
{
	mlx_mouse_get_pos(cub->mlx_ptr, cub->win_ptr, &cub->mouse_x, &cub->mouse_y);
	if (b == 's')
	{
		if ((cub->mouse_x >= (WINDOW_X / 2) - i->width / 2)
			&& (cub->mouse_x <= (WINDOW_X / 2) + i->width / 2)
			&& (cub->mouse_y >= ((WINDOW_Y - 100) / 2) - i->height)
			&& (cub->mouse_y <= (WINDOW_Y - 100) / 2))
			return (1);
	}
	else if (b == 'q')
	{
		if ((cub->mouse_x >= (WINDOW_X / 2) - i->width / 2)
			&& (cub->mouse_x <= (WINDOW_X / 2) + i->width / 2)
			&& (cub->mouse_y >= ((WINDOW_Y + 450) / 2) - i->height)
			&& (cub->mouse_y <= (WINDOW_Y + 450) / 2))
			return (1);
	}
	return (0);
}

/**
 * @brief Configure une texture de menu pour le rendu.
 *
 * La fonction setup_menu charge un fichier image XPM et le prépare pour le rendu en tant que
 * texture de menu. Il configure l'adresse de l'image et d'autres paramètres nécessaires à
 * l'utilisation dans le menu du jeu.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param tex pointeur vers la structure de configuration t_Texture représentant la texture du menu.
 * @param file Chemin du fichier vers le fichier image XPM à charger en tant que texture de menu.
 */
void	setup_menu(t_Cub3d *cub, t_TextureSetup *tex, char *file)
{
	load_xpm(cub, tex->img, file);
	(void)tex->path;
	tex->img->addr = mlx_get_data_addr(tex->img->img_ptr, &tex->img->bpp,
			&tex->img->len, &tex->img->endian);
}

/**
 * @brief Initialise le menu de démarrage du jeu.
 *
 * La fonction start_menu initialise le menu de démarrage du jeu,
 * l'apparence des boutons et leur état initial. Il configure les composants du
 * menu Démarrer pour l'affichage.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @return renvoie 0 si l'initialisation du menu Démarrer est réussie.
 */
int	start_menu(t_Cub3d *cub)
{
	t_Menu	*m;

	cub->main = ft_calloc(1, sizeof(t_Menu));
	m = cub->main;
	cub->menu_active = true;
	m->start = ft_calloc(1, sizeof(t_TextureSetup));
	m->start->img = ft_calloc(1, sizeof(t_ImageControl));
	m->quit = ft_calloc(1, sizeof(t_TextureSetup));
	m->quit->img = ft_calloc(1, sizeof(t_ImageControl));
	setup_menu(cub, m->start, "./sprites/Menu/start_00.xpm");
	setup_menu(cub, m->quit, "./sprites/Menu/quit_00.xpm");
	cub->menu_ok = true;
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, m->start->img->img_ptr,
		(WINDOW_X / 2) - m->start->img->width / 2,
		((WINDOW_Y - 100) / 2) - m->start->img->height);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, m->quit->img->img_ptr,
		(WINDOW_X / 2) - m->quit->img->width / 2,
		((WINDOW_Y + 450) / 2) - m->quit->img->height);
	return (0);
}