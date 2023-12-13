#include "../../headers/cub3d.h"

/**
 * @brief Applique un effet de shader à une couleur donnée.
 *
 * La fonction 'apply_shader' prend une couleur d'entrée et applique un effet de
 * shader basé sur l'identifiant fourni. Les effets de shader modifient la luminosité
 * de la couleur.
 *
 * @param color La couleur d'origine à laquelle l'effet de shader sera appliqué.
 * @param id Un identifiant spécifiant l'effet de shader à appliquer:
 *      -'id == 1': Aucun effet de shader n'est appliqué; la couleur d'origine est
 * retourné.
 *      -'id == 2' : Un effet de shader assombrissant est appliqué (60% d'obscurité).
 *      -'id == 3' : Un effet de shader assombrissant plus fort est appliqué (40%
 * obscurité).
 * - 'id = = 4': Aucun effet de shader n'est appliqué; la couleur d'origine est retourné.
 * @return renvoie la couleur modifiée après l'application de l'effet de shader.
 */
int	apply_shader(int color, int id)
{
	float	d;
	int		r;
	int		g;
	int		b;

	if (id == 1 || id == 9)
		return (color);
	if (id == 2)
		d = 0.6;
	if (id == 3)
		d = 0.4;
	if (id == 4)
		d = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= d;
	g *= d;
	b *= d;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

/**
 * @brief Récupère l'adresse mémoire des données de pixels d'une texture.
 *
 * La fonction 'get_texture_addr' prend une structure 't_ImageControl' et renvoie
 * l'adresse mémoire des données de pixel pour la texture associée. Il alloue de la mémoire
 * pour un nouveau tableau d'entiers, copie les données de pixels de la texture et renvoie
 * l'adresse du nouveau tableau.
 *
 * @param i pointe vers la structure 't_ImageControl'.
 * @return l'adresse mémoire des données de pixels pour la texture.
 */
int	*get_texture_addr(t_ImageControl *i)
{
	int	*tmp;
	int	row_start;
	int	y;

	tmp = ft_calloc(i->height * i->width, sizeof(int));
	if (!tmp)
		return (NULL);
	i->addr = mlx_get_data_addr(i->img_ptr, &(i->bpp), &(i->len), &(i->endian));
	y = 0;
	while (y < i->height)
	{
		row_start = y * i->width;
		ft_memcpy(tmp + row_start, i->addr + row_start, i->width * sizeof(int));
		y++;
	}
	return (tmp);
}

/**
 * @brief Récupère la structure 't_ImageControl' associée à un identifiant de texture.
 *
 * La fonction 'get_img_struct' renvoie la structure 't_ImageControl' associée à un identifiant
 * de texture spécifié à partir de la structure `t_Cub3d'.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param id Un identifiant spécifiant la texture à récupérer.
 * @return un pointeur vers la structure 't_ImageControl' associée à la
 * ID de texture spécifié.
 */
t_ImageControl	*get_img_struct(t_Cub3d *cub, int id)
{
	if (id == 1)
		return (cub->map->tex_north->img);
	if (id == 2)
		return (cub->map->tex_south->img);
	if (id == 3)
		return (cub->map->tex_west->img);
	if (id == 4)
		return (cub->map->tex_east->img);
	if (id == 9)
		return (cub->map->tex_door->img);
	return (NULL);
}

/**
 * @brief Calculez le point de contact exact entre le rayon et le mur.
 *
 * La fonction 'get_wall_x' calcule la valeur 'wall_x', qui représente 
 * le point de contact exact entre le rayon et le mur, par rapport à la position du joueur.
 * Il est utilisé pendant le processus de lancer de rayons.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param c Pointeur vers la structure 't_CameraConfig' contenant les données
 * de configuration de la caméra.
 * @return la valeur 'wall_x' représentant le point de contact avec le mur.
 */
double	get_wall_x(t_Cub3d *cub, t_CameraConfig *c)
{
	double	wall_x;

	if (!c->side)
	{
		wall_x = cub->player->pos_y + c->perp_wd * c->raydir_y;
		wall_x -= c->map_y;
	}
	else
	{
		wall_x = cub->player->pos_x + c->perp_wd * c->raydir_x;
		wall_x -= c->map_x;
	}
	return (wall_x);
}

/**
 * @brief Appliquez une texture à un mur et envisagez des effets de shader.
 *
 * La fonction 'apply_texture' applique une texture à un mur à la colonne d'écran spécifiée
 * 'x' tout en tenant compte de l'effet de shader. Il calcule les coordonnées de texture,
 * y compris "tx" et "ty", en fonction de la position et de l'orientation du mur. La fonction
 * parcourt ensuite la hauteur du mur et applique la texture à chaque pixel du mur, en tenant
 * compte du décalage de texture et de l'effet de shader.
 *
 * @param Pointeur cur vers la structure 't_Cub3d'.
 * @param c Pointeur vers la structure 't_CameraConfig' contenant les données
 * de configuration de la caméra.
 * @param x La colonne d'écran en cours de traitement.
 * @param id Un identifiant spécifiant la texture à appliquer (nord, sud, ouest, est).
 */
void	apply_texture(t_Cub3d *cub, t_CameraConfig *c, int x, int id)
{
	double			wall_x;
	double			tx;
	double			ty;
	int				y;
	t_ImageControl	*img;

	img = get_img_struct(cub, id);
	wall_x = get_wall_x(cub, c);
	tx = (int)(wall_x * (double)img->width);
	tx = img->width - tx - 1;
	c->tex_step = 1.0 * img->width / c->line_height;
	c->tex_pos = (c->draw_start - WINDOW_Y / 2 + c->line_height) * c->tex_step;
	y = c->draw_start;
	while (y++ < c->draw_end)
	{
		ty = ((int) c->tex_pos & ((img->height / 2) - 1));
		c->tex_pos += c->tex_step;
		if (x >= 0 && y >= 0 && tx >= 0 && ty >= 0)
		{
			c->color = my_mlx_pixel_get(img, tx, ty);
			c->color = apply_shader(c->color, c->wall_dir);
			my_mlx_pixel_put(cub->img, x, y, c->color);
		}
	}
}