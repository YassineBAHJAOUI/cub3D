#include "../../headers/cub3d.h"

/**
 * @brief Nettoyer et libérer les ressources utilisées par (GNL)
 *
 * La fonction 'ft_clean_gnl' est responsable de la libération de la mémoire
 * et de la fermeture du descripteur de fichier associé à la fonction Get Next Line (GNL).
 * Il parcourt les lignes de sortie du GNL, libérant la mémoire de chaque ligne,
 * puis ferme le descripteur de fichier.
 * Cette fonction doit être appelée lorsque l'interface graphique n'est plus nécessaire
 * pour éviter les fuites de mémoire et les fuites de data.
 *
 * @param fd Le descripteur de fichier associé à la fonction GNL.
 * @param line Un pointeur sur la dernière ligne de sortie GNL ou NULL si GNL n'est pas dans
 * utilisation.
 */
void	ft_clean_gnl(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

/**
 * @brief Ouvrez le fichier de carte pour le lire.
 *
 * Cette fonction ouvre le fichier de map spécifié dans le 'filename'
 * de la structure 't_MapConfig' dans 't_Cub3d' fourni.
 * Il utilise l'indicateur O_RDONLY pour ouvrir le fichier en lecture seule.
 * Si le fichier ne peut pas être ouvert, la fonction libère la mémoire allouée,
 * termine le programme avec un message d'erreur et définit l'indicateur 'crash'
 * sur true pour indiquer une erreur.
 *
 * @param cub Pointer vers la structure t_Cub3d.
 */
void	ft_open(t_Cub3d *cub)
{
	cub->map->fd = open(cub->map->filename, O_RDONLY);
	if (cub->map->fd < 0)
	{
		free_main(cub);
		printf("Error: fatal: cannot open map file\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * Crée un fichier .map temporaire contenant les données cartographiques extraites du fichier .map d'origine.
 *
 * @param cub Un pointeur vers la structure Cub3d.
 * @param line La ligne de données actuelle du fichier de carte d'origine.
 *
 * @note Cette fonction ouvre un fichier de carte temporaire nommé "./.map " et y écrit les données
 * cartographiques extraites du fichier .map d'origine. La fonction continue de lire les lignes du
 * fichier de carte d'origine à l'aide de la fonction 'get_next_line' et de les écrire dans le fichier
 * de carte temporaire jusqu'à ce que la fin du fichier soit atteinte. Le pointeur 'line' fourni sera
 * libéré après chaque opération d'écriture
 */
void	create_temp_map(t_Cub3d *cub, char *line)
{
	cub->map->temp_fd = open("./.map", O_RDWR | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR);
	while (line)
	{
		write(cub->map->temp_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(cub->map->fd);
	}
}

/**
 *  @brief fonction d'aide pour ignorer les lignes d'informations du map.
 *
 * Cette fonction d'aide est utilisée par la fonction skip_info pour traiter
 * les lignes d'informations de la carte et mettre à jour le compteur de skip
 * en conséquence. Il vérifie les différents préfixes associés aux chemins
 * de texture et aux paramètres de couleur, incrémentant le compteur de sauts
 * lorsque ces lignes sont rencontrées. De plus, il garantit que la première
 * ligne de données maps (contenant " 1 " pour les murs) est
 * correctement localisée et non ignorée.
 *
 * @param cub Pointeur vers la structure t_Cub3d .
 * @param line Un pointeur vers la ligne en cours de traitement à partir du fichier de mappage.
 * @param skip Un pointeur vers le compteur de skip, mis à jour pendant le processus.
 * @return Renvoie un pointeur sur la ligne suivante après le traitement.
 */
static char	*skip_info2(t_Cub3d *cub, char *line, int *skip)
{
	if (ft_strchr("\n", line[0]))
	{
		cub->map->skip_counter++;
		free(line);
		line = get_next_line(cub->map->fd);
	}
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2)
		|| (BONUS && !ft_strncmp("DO ", line, 3)))
		(*skip)++;
	if (ft_strchr("1\t ", line[0]) && *skip != SKIP + BONUS - 1)
		return (NULL);
	cub->map->skip_counter++;
	free(line);
	line = get_next_line(cub->map->fd);
	return (line);
}

/**
 * @brief Ignorez les lignes d'informations map et localisez le début des données map.
 *
 * Cette fonction est responsable de la lecture du fichier de carte et de l'omission des
 * lignes d'informations de carte initiales, telles que les chemins de texture et les paramètres
 * de couleur. Il continue à parcourir le fichier jusqu'à ce qu'il localise la première ligne de
 * données cartographiques réelles contenant "1" pour représenter les murs. Une fois la première
 * ligne de données cartographiques trouvée, la fonction renvoie un pointeur vers celle-ci, permettant
 * un traitement ultérieur de la disposition de la carte. La fonction utilise un compteur de sauts pour
 * garder une trace du nombre de lignes sautées pendant le processus.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param line Un pointeur vers la ligne en cours de traitement à partir du fichier de map.
 * @return Renvoie un pointeur sur la première ligne de données cartographiques réelles, ou NULL si elle n'est pas trouvée.
 */
char	*skip_info(t_Cub3d *cub, char *line, int i)
{
	int	skip;

	skip = 0;
	while (skip < SKIP + BONUS)
		line = skip_info2(cub, line, &skip);
	if (!line)
		return (NULL);
	while (ft_strchr("\n", line[0]))
	{
		free(line);
		line = get_next_line(cub->map->fd);
	}
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_strncmp("1", &line[i], 1))
				return (line);
			i++;
		}
		free(line);
		line = get_next_line(cub->map->fd);
	}
	return (NULL);
}