#include "../../headers/cub3d.h"

/**
 * @brief Vérifiez la validité des paramètres de couleur du sol et du plafond dans 
 * les informations de map.
 *
 * Cette fonction valide l'exactitude des paramètres de couleur du sol et du plafond
 * dans la description de la scène. Il vérifie les paramètres de couleur valides pour
 * le sol et le plafond, en veillant à ce que chaque valeur de couleur se situe dans la
 * plage valide. Si des couleurs valides sont trouvées, la fonction stocke les paramètres
 * de couleur dans le tableau 'colors' de la structure 't_MapConfig' dans `t_Cub3d ' fourni.
 *
 * Si les paramètres de couleur sont valides, la fonction renvoie 0. Si un paramètre de
 * couleur non valide ou en double est rencontré, la fonction renvoie 1, indiquant une erreur.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param line Un pointeur vers la ligne en cours de traitement à partir du fichier de map.
 * @return Renvoie 0 si les paramètres de couleur sont valides, ou 1 si une erreur se produit.
 */
int	has_valid_info3(t_Cub3d *cub, char *line)
{
	if (!ft_strncmp("F ", line, 2))
	{
		if (!cub->map->colors[0])
			put_floor_ceil_color(cub, line, 0, 0);
		else
			return (1);
	}
	else if (!ft_strncmp("C ", line, 2))
	{
		if (!cub->map->colors[1])
			put_floor_ceil_color(cub, line, 1, 0);
		else
			return (1);
	}
	return (0);
}

/**
 * @brief Check the validity of texture path settings for map elements.
 *
 * This function checks the correctness of texture path settings for specific
 * map elements within the scene description. It examines the provided `line`
 * to determine if it represents a valid texture path for the north (NO),
 * south (SO), west (WE), or east (EA) side of the map. If a valid texture
 * path is found, it invokes the `set_tex_path` function to store the path
 * in the appropriate member of the `t_MapConfig` structure within the
 * provided `t_Cub3d` context. If the texture path setting is invalid or a
 * duplicate, the function returns 1 to indicate an error.
 *
 * @param cub Pointer to the t_Cub3d structure containing program
 * context and data.
 * @param line A pointer to the current line being processed from the map file.
 * @return Returns 0 if the texture path setting is valid,
 * or 1 if an error occurs.
 */
int	set_tex_path(t_Cub3d *cub, char *path, int direction)
{
	char	*temp;

	temp = ft_strdup(path + 3);
	if (direction == 1 && !cub->map->tex_north->path)
		cub->map->tex_north->path = ft_strtrim(temp, " \t\n");
	else if (direction == 2 && !cub->map->tex_south->path)
		cub->map->tex_south->path = ft_strtrim(temp, " \t\n");
	else if (direction == 3 && !cub->map->tex_west->path)
		cub->map->tex_west->path = ft_strtrim(temp, " \t\n");
	else if (direction == 4 && !cub->map->tex_east->path)
		cub->map->tex_east->path = ft_strtrim(temp, " \t\n");
	else if (direction == 9 && !cub->map->tex_door->path)
		cub->map->tex_door->path = ft_strtrim(temp, " \t\n");
	else
		return (free(temp), 1);
	return (free (temp), 0);
}

/**
 * @brief Vérifiez et définissez des informations supplémentaires dans la configuration Cub3D.
 *
 * La fonction 'has_valid_info2' vérifie si la ligne donnée correspond à des informations supplémentaires
 * dans le fichier de carte, telles que des détails liés aux bonus. Il vérifie les informations valides
 * relatives aux textures pour les murs et les portes nord, sud, ouest, est
 * Si des informations valides sont trouvées, il appelle les fonctions appropriées pour définir
 * les chemins de texture correspondants dans la configuration 'cub'.
 *
 * Pointeur @ param cub vers la configuration principale de Cub3D.
 * @param line La ligne du fichier de carte en cours de traitement.
 * @return Renvoie 1 si une erreur se produit (par exemple, chemin non valide), 0 sinon.
 */
int	has_valid_info2(t_Cub3d *cub, char *line)
{
	if (check_north_south(cub, line))
		return (1);
	else if (check_west_east(cub, line))
		return (1);
	else if (BONUS && !ft_strncmp("DO ", line, 3))
	{
		if (set_tex_path(cub, line, 9))
			return (1);
	}
	return (0);
}

/**
 * @brief Vérifie si la carte dans le descripteur de fichier donné est valide.
 *
 * La fonction 'ft_check_d' vérifie si les données de la carte dans le descripteur
 * de fichier spécifié sont valides selon le format de carte Cub3D. Il parcourt le
 * fichier ligne par ligne jusqu'à ce qu'il trouve la section de la carte, puis il
 * vérifie que la carte ne contient que des caractères valides ('1' pour les murs,
 * ' 'pour les espaces vides et' \n ' pour les fins de ligne). Tout autre caractère
 * indique une carte non valide.
 *
 * @param line Un pointeur sur la ligne en cours de traitement.
 * @param fd Le descripteur de fichier du fichier de carte.
 *
 * @return Renvoie 0 si la carte est valide, 1 si la carte n'est pas valide ou
 * exmple2/mandatory/src/map_files/map_closed_utils.csi une erreur se produit.
 */
static int ft_check_d(char *line, int fd)
{
	int		i;
	bool	is_map;
	is_map = false;
	while (line)
	{
		i = 0;
		while (line[i] && !is_map)
		{
			if (line[i] != '1' && line[i] != ' '
				&& line[i] != '\t' && line[i] != '\n')
				return (ft_clean_gnl(fd, line), 1);
			if (line[i] == '1')
				is_map = true;
			i++;
		}
		if (is_map)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	ft_clean_gnl(fd, line);
	return (0);
}

/**
 * @brief Vérifiez et définissez la configuration liée à la carte dans la structure Cub3D.
 *
 * La fonction ('has_valid_info') est responsable de la lecture et du traitement des informations
 * de configuration liées à la carte à partir du fichier de carte.
 * Il gère l'analyse des chemins de texture pour les murs nord, sud, ouest et est,
 * ainsi que les couleurs pour le plafond et le sol.
 * Selon que les fonctionnalités bonus sont activées ou non, il peut également rechercher des informations
 * supplémentaires relatives aux bonus. Si des erreurs sont rencontrées lors de l'analyse
 * (par exemple, des chemins non valides), la fonction renvoie un code d'erreur.
 *
 * @param cub Pointeur vers la configuration principale de Cub3D.
 * @return 1 si une erreur se produit lors de l'analyse, 0 sinon.
 */
int	has_valid_info(t_Cub3d *cub, char *line)
{
	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!BONUS)
	{
		while ((!cub->map->tex_north->path || !cub->map->tex_south->path
				|| !cub->map->tex_west->path || !cub->map->tex_east->path)
			|| (!cub->map->colors[0] || !cub->map->colors[1]))
		{
			if (ft_strchr("D1\t ", line[0]))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			if (has_valid_info2(cub, line))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			else if (has_valid_info3(cub, line))
				return (ft_clean_gnl(cub->map->fd, line), 1);
			free(line);
			line = get_next_line(cub->map->fd);
		}
		if (ft_check_d(line, cub->map->fd))
			return (1);
	}
	else if (fill_bonus_info(cub, line))
		return (1);
	return (0);
}