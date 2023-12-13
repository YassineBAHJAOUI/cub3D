#include "../../headers/cub3d.h"

/**
 * @brief Vérifiez et définissez le chemin de texture pour les murs nord et sud.
 *
 * La fonction 'check_north_south' vérifie si la ligne donnée correspond au chemin
 * de texture pour les murs nord ou sud (par exemple, "NO texture_path" ou "SO texture_path").
 * Si un chemin valide est trouvé, il appelle 'set_tex_path' pour définir le chemin de texture
 * approprié dans la configuration 'cub'.
 *
 * @param cub Pointeur vers la configuration principale de Cub3D.
 * @param line La ligne du fichier de carte en cours de traitement.
 * @return Renvoie 1 si une erreur se produit (par exemple, chemin non valide), 0 sinon.
 */
int	check_north_south(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("NO ", line, 3))
	{
		if (set_tex_path(cub, line, 1))
			return (1);
	}
	else if (!ft_strncmp("SO ", line, 3))
	{
		if (set_tex_path(cub, line, 2))
			return (1);
	}
	return (0);
}

/**
 * @brief Vérifiez et définissez le chemin de texture pour les murs ouest et est.
 *
 * La fonction 'check_west_east' vérifie si la ligne donnée correspond au chemin de
 * texture pour les murs ouest ou est (par exemple, "WE texture_path" ou "EA texture_path").
 * Si un chemin valide est trouvé, il appelle 'set_tex_path' pour définir le chemin de texture
 * approprié dans la configuration 'cub'.
 *
 * @param cub Pointeur vers la configuration principale de Cub3D.
 * @param line La ligne du fichier de carte en cours de traitement.
 * @return Renvoie 1 si une erreur se produit (par exemple, chemin non valide), 0 sinon.
 */
int	check_west_east(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("WE ", line, 3))
	{
		if (set_tex_path(cub, line, 3))
			return (1);
	}
	else if (!ft_strncmp("EA ", line, 3))
	{
		if (set_tex_path(cub, line, 4))
			return (1);
	}
	return (0);
}

/**
 * @brief Remplissez les informations bonus dans la configuration Cub3D.
 *
 * La fonction 'fill_bonus_info' extrait et remplit les informations relatives
 * aux bonus dans la configuration 'cub', telles que les chemins de texture et
 * les couleurs. Il continue à lire les lignes du fichier de carte jusqu'à ce
 * que toutes les informations de bonus requises soient trouvées ou jusqu'à ce
 * qu'une erreur se produise. Cette fonction est utilisée lors de l'analyse des
 * fichiers map.
 *
 * @param cub Pointeur vers la configuration principale de Cub3D.
 * @param line La ligne en cours de traitement à partir du fichier de carte.
 * @return Renvoie 1 si une erreur se produit, 0 sinon.
 */
int	fill_bonus_info(t_Cub3d *cub, char *line)
{
	while ((!cub->map->tex_north->path || !cub->map->tex_south->path
			|| !cub->map->tex_west->path || !cub->map->tex_east->path)
		|| (!cub->map->colors[0] || !cub->map->colors[1])
		|| !cub->map->tex_door->path)
	{
		if (!line)
			return (ft_clean_gnl(cub->map->fd, line), 1);
		if (ft_strchr("1\t ", line[0]))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		if (has_valid_info2(cub, line))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		else if (has_valid_info3(cub, line))
			return (ft_clean_gnl(cub->map->fd, line), 1);
		free(line);
		line = get_next_line(cub->map->fd);
	}
	ft_clean_gnl(cub->map->fd, line);
	return (0);
}