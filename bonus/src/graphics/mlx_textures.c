#include "../../headers/cub3d.h"

/**
 * @brief Charge une image XPM en tant que texture.
 *
 * La fonction 'load_xpm' charge un fichier image XPM et le stocke en tant que texture
 * dans la structure 't_ImageControl'. Il définit les propriétés 'width' et 'height'
 * de l'image et la propriété 'img_ptr' sur le pointeur d'image chargé.
 *
 * @param c Pointeur vers la structure 't_Cub3d'.
 * @param i pointe vers la structure 't_ImageControl' représentant l'image à charger.
 * @param file Le nom de fichier de l'image XPM à charger.
 */
void	load_xpm(t_Cub3d *c, t_ImageControl *i, char *file)
{
	i->height = 0;
	i->width = 0;
	i->img_ptr = mlx_xpm_file_to_image(c->mlx_ptr, file, &i->width, &i->height);
	if (!i->img_ptr)
	{
		free_main(c);
		printf("Error: Failed loading %s texture", file);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Vérifie l'accès aux fichiers de texture dans Cub3D.
 *
 * La fonction 'check_access' est chargée de vérifier l'accessibilité des fichiers de texture
 * utilisés dans Cub3D. Il tente d'ouvrir chacun des quatre chemins de texture fournis en utilisant
 * l'indicateur 'O_RDONLY' et stocke les descripteurs de fichier correspondants. Après avoir tenté
 * d'ouvrir tous les fichiers, la fonction ferme les descripteurs de fichiers ouverts.
 * Si l'un des fichiers ne peut pas être ouvert ou accessible, la fonction renvoie 1 pour indiquer
 * une erreur, sinon elle renvoie 0 pour indiquer un accès réussi.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return Renvoie 0 si l'accès à tous les fichiers de texture est réussi, ou 1 s'il y a une erreur
 * d'accès à l'un des fichiers.
 */
int	check_access(t_Cub3d *cub)
{
	int	fd[4 + BONUS];

	fd[0] = open(cub->map->tex_north->path, O_RDONLY);
	fd[1] = open(cub->map->tex_south->path, O_RDONLY);
	fd[2] = open(cub->map->tex_west->path, O_RDONLY);
	fd[3] = open(cub->map->tex_east->path, O_RDONLY);
	if (BONUS)
	{
		fd[4] = open(cub->map->tex_door->path, O_RDONLY);
		close(fd[4]);
		if (fd[4] < 0)
			return (1);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[2] != -1)
		close(fd[2]);
	if (fd[3] != -1)
		close(fd[3]);
	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
		return (1);
	return (0);
}

/**
 * @brief Convertit et charge les textures pour le lancer de rayons.
 *
 * La fonction 'convert_textures' initialise les textures utilisées pour le rayon
 * dans la structure 't_CameraConfig'. Il charge les fichiers image XPM pour les murs nord,
 * sud,ouest et est, les convertit en tableaux entiers et les stocke dans le tableau de 'tex'.
 * De plus, il alloue de la mémoire pour chaque texture et garantit le chargement réussi des
 * fichiers de texture.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return 0 en cas de succès, 1 s'il y a eu une erreur lors du chargement de la texture.
 */
int	convert_textures(t_Cub3d *cub)
{
	t_CameraConfig	*c;

	c = cub->cam;
	c->tex = ft_calloc(4 + BONUS, sizeof(int *));
	if (!cub->cam->tex)
		return (1);
	load_xpm(cub, cub->map->tex_north->img, cub->map->tex_north->path);
	load_xpm(cub, cub->map->tex_south->img, cub->map->tex_south->path);
	load_xpm(cub, cub->map->tex_west->img, cub->map->tex_west->path);
	load_xpm(cub, cub->map->tex_east->img, cub->map->tex_east->path);
	c->tex[0] = get_texture_addr(cub->map->tex_north->img);
	c->tex[1] = get_texture_addr(cub->map->tex_south->img);
	c->tex[2] = get_texture_addr(cub->map->tex_west->img);
	c->tex[3] = get_texture_addr(cub->map->tex_east->img);
	if (BONUS)
	{
		load_xpm(cub, cub->map->tex_door->img, cub->map->tex_door->path);
		c->tex[4] = get_texture_addr(cub->map->tex_door->img);
	}
	c->tex_vector = true;
	return (0);
}

/**
 * @brief Vérifie si un chemin de fichier donné correspond à un fichier image XPM.
 *
 * Cette fonction vérifie si le chemin de fichier donné correspond à un fichier image
 * XPM en fonction de son extension. Il compare l'extension de fichier avec ".xpm" et
 * renvoie 1 si le fichier est une image XPM, ou 0 si ce n'est pas le cas.
 *
 * @param cub Pointeur vers la structure t_Cub3d .
 * @param id L'ID correspondant au chemin de texture à vérifier:
 * 1 pour la texture nord, 2 pour la texture sud, 3 pour la texture ouest, 4 pour
 * texture orientale.
 * @return Renvoie 1 si le chemin du fichier correspond à une image XPM,ou 0 sinon.
 */
int	is_xpm(t_Cub3d *cub, int id)
{
	char	*filetype;
	char	*filename;
	int		len;
	int		i;

	filetype = ".xpm";
	if (id == 1)
		filename = ft_strdup(cub->map->tex_north->path);
	else if (id == 2)
		filename = ft_strdup(cub->map->tex_south->path);
	else if (id == 3)
		filename = ft_strdup(cub->map->tex_west->path);
	else if (id == 4)
		filename = ft_strdup(cub->map->tex_east->path);
	else if (id == 9)
		filename = ft_strdup(cub->map->tex_door->path);
	i = 4;
	len = ft_strlen(filename) - 1;
	while (i)
		if (filename[len--] != filetype[--i])
			return (free(filename), 1);
	return (free(filename), 0);
}

/**
 * @brief Vérifie la validité des chemins des fichiers de texture.
 *
 * Cette fonction vérifie la validité des chemins des fichiers de texture dans la structure t_Cub3d. Il appelle la fonction is_xpm pour chaque chemin de texture (nord, sud, ouest et est) et renvoie 1 si l'un des chemins de texture n'est pas une image XPM, indiquant une texture non valide.Si tous les chemins de texture sont des images XPM valides, elle renvoie 0.
 *
 * Pointeur @ param cub vers la structure t_Cub3d.
 * @return Renvoie 1 si l'un des chemins de texture est une image XPM non valide, ou 0 si tous sont valides.
 */
int	check_tex_validity(t_Cub3d *cub)
{
	cub->cam->tex_vector = false;
	cub->map->tex_north->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_south->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_west->img = ft_calloc(1, sizeof(t_ImageControl));
	cub->map->tex_east->img = ft_calloc(1, sizeof(t_ImageControl));
	if (BONUS)
		cub->map->tex_door->img = ft_calloc(1, sizeof(t_ImageControl));
	if (is_xpm(cub, 1) || is_xpm(cub, 2)
		|| is_xpm(cub, 3) || is_xpm(cub, 4) || (BONUS && is_xpm(cub, 9)))
		return (1);
	if (check_access(cub))
		return (1);
	return (0);
}