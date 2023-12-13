#include "../../headers/cub3d.h"

/**
 * Obtenez un code couleur à partir d'un tableau de couleurs 256x256x256.
 *
 * Cette fonction prend un tableau de couleurs tridimensionnel et recherche
 * le premier élément non nul (couleur). Il convertit ensuite les valeurs RVB
 * en un code de couleur hexadécimal et le renvoie. Si aucune couleur différente
 * de zéro n'est trouvée, elle renvoie 0 (noir).
 *
 * @param color Un tableau de 256x256x256 représentant les couleurs (format RVB).
 * @return renvoie un entier non signé représentant le code couleur au format hexadécimal (0xRRGGBB).
 */
static int	get_color(int color[256][256][256])
{
	int	r;
	int	g;
	int	b;

	r = 0;
	while (r < 256)
	{
		g = 0;
		while (g < 256)
		{
			b = 0;
			while (b < 256)
			{
				if (color[r][g][b])
					return (0x010000 * r + 0x000100 * g + b);
				b++;
			}
			g++;
		}
		r++;
	}
	return (0);
}

/**
 * Définir une couleur de pixel dans une image.
 *
 * Cette fonction définit la couleur d'un pixel aux coordonnées spécifiées (x, y)
 * dans une image. Il faut une structure de contrôle d'image ('img'), la position
 * (x, y) du pixel et la valeur de couleur à définir.
 *
 * @param img Un pointeur vers la structure de contrôle de l'image représentant l'image.
 * @param x La coordonnée x du pixel.
 * @param y La coordonnée y du pixel.
 * @param color La valeur de couleur à définir (au format entier).
 */
void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * Rendu du plafond et du sol de la fenêtre de jeu.
 *
 * Cette fonction affiche le plafond et le sol de la fenêtre de jeu en définissant
 * les couleurs des pixels dans le tampon d'image ('cub->img') pour toute la zone
 * de la fenêtre. Il utilise les couleurs définies dans la structure ('cub->map')
 * pour le plafond et le sol.
 *
 * @param cub Un pointeur vers la structure Cub3d.
 */
void	render_ceilling_floor(t_Cub3d *cub)
{
	int				x;
	int				y;
	unsigned int	cc;
	unsigned int	fc;

	x = 0;
	cc = get_color(cub->map->ceilling_c);
	fc = get_color(cub->map->floor_c);
	while (x++ < WINDOW_X)
	{
		y = 0;
		while (y++ <= WINDOW_Y / 2)
			my_mlx_pixel_put(cub->img, x, y, cc);
		while (y < WINDOW_Y)
		{
			my_mlx_pixel_put(cub->img, x, y, fc);
			y++;
		}
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
}

/**
 * @brief Initialise les graphismes, les ressources et les composants principaux du jeu.
 *
 * La fonction "graphiques" joue un rôle central dans le projet Cub3D en configurant
 * l'ensemble de l'environnement de jeu. Il englobe l'initialisation des composants
 * graphiques, la création de la fenêtre de jeu et la configuration des actifs essentiels
 * et des variables d'état.
 *
 * Plus précisément, cette fonction gère les tâches suivantes:
 *
 * - Initialise la configuration de la caméra, essentielle pour le rayon.
 * - Valide et charge toutes les textures et ressources requises.
 * - Crée la fenêtre de jeu en utilisant la bibliothèque MLX avec une taille spécifiée.
 * - Prépare le tampon d'image du jeu pour le rendu.
 * - Initialise le menu Démarrer, permettant aux joueurs de commencer ou de quitter le jeu.
 * - Configure la minimap, qui donne un aperçu de la carte du jeu.
 * - Positionne et rend l'arme du joueur dans la vue du jeu.
 * - Place le personnage du joueur à la position de départ.
 * - Convertit les textures chargées en formats adaptés au rendu.
 *
 * Si l'une de ces étapes d'initialisation échoue, la fonction renvoie un code d'erreur (1)
 * pour indiquer qu'il y a eu un problème avec le processus d'installation. Une valeur de
 * retour de 0 signifie que les graphismes et l'environnement de jeu sont correctement configurés
 * et prêts pour le jeu.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @return renvoie 0 si l'initialisation graphique est réussie, 1 s'il y a des erreurs.
 */
int	graphics(t_Cub3d *cub)
{
	if (camera_init(cub))
		return (1);
	if (check_tex_validity(cub))
		return (1);
	cub->mlx_ptr = mlx_init();
	cub->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_X, WINDOW_Y, "CUB3D");
	cub->img->img_ptr = mlx_new_image(cub->mlx_ptr, WINDOW_X, WINDOW_Y);
	cub->img->addr = mlx_get_data_addr(cub->img->img_ptr,
			&cub->img->bpp, &cub->img->len, &cub->img->endian);
	if (start_menu(cub))
		return (1);
	init_minimap(cub);
	player_gun(cub, cub->player);
	cub->graphics_ok = true;
	set_player_position(cub);
	if (convert_textures(cub))
		return (1);
	cub->files_ok = true;
	return (0);
}