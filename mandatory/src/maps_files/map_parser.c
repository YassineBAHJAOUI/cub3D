#include "../../headers/cub3d.h"

/**
 * @brief Vérifiez si le fichier de description de scène fourni a un type de carte valide
 * pour le projet Cub3D.
 *
 * Cette fonction vérifie si le fichier de description de scène fourni, représenté par la
 * structure `cub`, a un type de carte valide indiqué par le extension `.cub`. Il compare
 * les caractères dans l'ordre inverse, en commençant par la fin du nom de fichier, avec les
 * caractères dans le extension `.cub`.
 *
 * De plus, la fonction ouvre le fichier spécifié dans la structure `cub` en utilisant
 * l'appel système 'open' avec des autorisations en lecture seule. Si le fichier ne peut pas
 * être ouvert, la fonction renvoie 1 pour indiquer une erreur.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @return Renvoie 1 si le fichier a un type de carte valide ou ne peut pas être ouvert,
 * 0 si le fichier est valide et ouvert avec succès.
 */
int	is_valid_map_file(t_Cub3d *cub)
{
	char	*filetype;
	int		len;
	int		i;

	filetype = ".cub";
	len = ft_strlen(cub->map->filename) - 1;
	i = 4;
	while (i)
		if (cub->map->filename[len--] != filetype[--i])
			return (1);
	return (0);
}

/**
 * @brief Analyse et valide les éléments du jeu à partir d'une ligne du fichier de
 * configuration de la carte.
 *
 * La fonction `parse_elements2` analyse et valide les éléments du jeu à partir d'une
 * ligne du fichier de configuration de la carte. Il vérifie si le caractère à un index
 * spécifique de la ligne appartient à un ensemble valide de caractères défini par la variable
 * `charset`, qui inclut les symboles de la carte('0', '1', 'N', 'S', 'E', 'W'), nouvelle ligne('n')
 * et caractères de tabulation ('t'). La fonction prend également en compte les éléments
 * bonus lorsque l'indicateur "BONUS" est activé.
 *
 * Si le personnage n'est pas valide ou si une erreur se produit lors du réglage de l'orientation
 * du joueur en fonction du personnage, la fonction renvoie un code d'erreur (1). Sinon,
 * il renvoie 0, indiquant une analyse et une validation réussies.
 *
 * Cette fonction est essentielle pour traiter les éléments de configuration de la carte
 * et garantir l'intégrité des données de jeu.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 * @param line Une ligne du fichier de configuration de la carte.
 * @param i L'index du caractère à analyser et à valider dans la ligne.
 * @return Renvoie une valeur entière indiquant le succès (0) ou l'échec (1).
 */
static int	parse_elements2(t_Cub3d *cub, char *line, int i)
{
	char	*charset;

	charset = "01NSEW\n\t ";
	if (BONUS)
		charset = "019NSEW\n\t ";
	if (!ft_strchr(charset, line[i]))
		return (1);
	else if (set_player_orientation(cub, line[i]))
		return (1);
	return (0);
}

/**
 * @brief Analyse les éléments de la carte et l'orientation du lecteur à partir du fichier de carte.
 *
 * Cette fonction analyse les caractères individuels du fichier de carte, extrayant et validant chaque
 * caractère en tant qu'élément de carte valide. Pour rationaliser l'analyse et éviter d'avoir à ignorer
 * à plusieurs reprises les informations de texture et de couleur au début du fichier, la fonction crée
 * d'abord un fichier de carte temporaire qui contient uniquement la disposition de la carte.
 * Il lit ensuite chaque ligne du fichier de carte temporaire et traite chaque caractère à l'aide de la
 * fonction parse_elements2. Si un personnage n'est pas valide ou s'il y a un problème pour définir
 * l'orientation du joueur, la fonction renvoie une erreur. Sinon, il renvoie 0.
 *
 * En utilisant le fichier de carte temporaire, cette fonction garantit que le processus d'analyse maintient
 * une connexion avec les données du fichier de carte d'origine. Cette approche élimine efficacement
 * la nécessité de sauter à plusieurs reprises des informations superflues. Le fichier de carte temporaire
 * capture exclusivement la mise en page de la carte, rationalisant le processus d'analyse et éliminant le
 * besoin d'étapes redondantes.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param i un entier utilisé pour parcourir les caractères de la ligne.
 * @return Renvoie 0 si l'analyse est réussie, ou 1 si une erreur se produit.
 */
int	parse_elements(t_Cub3d *cub, int i, char *line)
{
	ft_open(cub);
	line = get_next_line(cub->map->fd);
	if (!line)
		return (1);
	line = skip_info(cub, line, 0);
	create_temp_map(cub, line);
	close(cub->map->temp_fd);
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (1);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (parse_elements2(cub, line, i))
				return (ft_clean_gnl(cub->map->temp_fd, line), 1);
			i++;
		}
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	return (ft_clean_gnl(cub->map->temp_fd, line), 0);
}

/**
 * Vérifie la validité de la carte dans la structure du jeu Cub3d.
 *
 * Cette fonction examine la structure Cub3d fournie pour déterminer si
 * les données cartographiques qu'elle contient sont valides. Il s'agit
 * d'analyser les éléments de la carte, de récupérer le nombre de lignes
 * et d'effectuer certains ajustements aux données de la carte.
 *
 * @param cub Pointeur vers une structure t_Cub3d.
 * @return Renvoie 1 si la carte est invalide, 0 si la carte est valide.
 */
int	check_map_validity(t_Cub3d *cub)
{
	if (parse_elements(cub, 0, NULL))
		return (1);
	if (!cub->player->orientation)
		return (1);
	get_map_n_lines(cub);
	cub->map->n_lines--;
	return (0);
}

/**
 * @brief Analyse et valide le fichier de carte de description de scène pour le projet Cub3D.
 *
 * Cette fonction est responsable de l'analyse du fichier de carte de description de scène fourni.
 * Il lit et valide le contenu du fichier de carte, en veillant à ce qu'il respecte les règles spécifiées,
 * telles que la structure de la carte et l'ordre des éléments corrects. Il valide également que le fichier
 * est du bon type extension (".cub").
 *
 * Si le fichier de map est valide, la fonction doit remplir les structures de données appropriées dans
 * l'objet 't_Cub3d' passé en tant que `cub`. Si le fichier n'est pas valide ou ne peut pas être lu,
 * la fonction libère la mémoire allouée, termine le programme avec un message d'erreur et définit
 * l'indicateur de `crash` sur true pour indiquer une erreur.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 */
int	parse_map_file(t_Cub3d *cub)
{
	if (has_valid_info(cub, NULL))
	{
		free_main(cub);
		printf("Error: Invalid or missing texture/color info\n");
		exit(EXIT_FAILURE);
	}
	if (!cub->map->filename || is_valid_map_file(cub))
	{
		free_main(cub);
		printf("Error: Cannot read map file or is of wrong type\n");
		exit(EXIT_FAILURE);
	}
	if (check_map_validity(cub))
	{
		free_main(cub);
		printf("Error: Map is invalid or contains invalid elements\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}