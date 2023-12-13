#include "../../headers/cub3d.h"

/**
 * @brief Détermine la validité des positions sur la carte du jeu matrice.
 *
 * La fonction 'get_matrix_borders' calcule la validité des positions autour d'une cellule
 * donnée dans la matrice de la carte du jeu. Il vérifie si les cellules situées en haut,
 * en bas, à gauche et à droite de la cellule spécifiée se trouvent dans les limites de
 * la matrice et stocke ces informations dans des variables booléennes.
 *
 * Cette fonction est utile pour vérifier les cellules adjacentes lors de l'exécution de
 * diverses opérations liées à la carte, telles que la détection de collision et l'analyse de la carte.
 *
 * @param m Pointeur vers la structure de configuration de la carte du jeu.
 * @param i L'index de ligne de la cellule en cours d'analyse.
 * @param j L'index de colonne de la cellule en cours d'analyse.
 * @note La validité des positions voisines est stockée dans les membres `up_valid`,
 * `down_valid`, `left_valid` et `right_valid` de la configuration de la carte.
 */
int	get_matrix_borders(t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j + 1] == '\0')
		if (m->matrix[i][j] != '1' || m->matrix[i][j] != ' ')
			return (1);
	m->up_valid = i - 1 >= 0 && j >= 0 && j < m->max_line_len - 1;
	m->down_valid = i + 1 < m->max_line_len - 1 && j >= 0
		&& j < m->max_line_len - 1;
	m->left_valid = j - 1 >= 0 && i >= 0 && i < m->n_lines;
	m->right_valid = j + 1 < m->max_line_len - 1 && i >= 0 && i < m->n_lines;
	return (0);
}

/**
 * @brief fonction utilitaire pour calculer la longueur de ligne maximale et le nombre total de lignes
 * dans la carte du jeu.
 *
 * La fonction `get_map_n_lines_utils` est un utilitaire utilisé pendant le processus d'analyse de la
 * carte pour calculer la longueur de ligne maximale et le nombre total de lignes dans la carte du jeu.
 * Il parcourt les caractères d'une ligne, en tenant compte à la fois des tabulations et des caractères
 * normaux. Les onglets sont utilisés pour la mise en forme de la carte, et leur nombre est utilisé pour
 * assurer une mise en forme cohérente. Pour chaque caractère, la fonction met à jour les onglets longueur
 * auxiliaire et nombre. Lorsqu'un caractère de tabulation est rencontré, il vérifie les règles de formatage.
 * Si un onglet fait partie d'une série d'onglets qui dépasse la règle de formatage, il contribue à la longueur
 * auxiliaire, garantissant un espacement cohérent dans la carte. Enfin, la fonction met à jour la longueur de
 * ligne maximale dans la structure de configuration de la carte et incrémente le nombre total de lignes.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param line Un pointeur vers la ligne d'entrée contenant les données de la carte.
 */
static	void	get_map_n_lines_utils(t_Cub3d *cub, char *line, int i, int tabs)
{
	int	aux_len;

	aux_len = 0;
	cub->map->n_lines++;
	while (line[i])
	{
		tabs++;
		if (line[i] == '\t')
		{
			if (tabs == 8)
				tabs = 0;
			while (tabs++ <= 8)
				aux_len++;
			tabs = 0;
		}
		else
			aux_len++;
		if (tabs >= 7)
			tabs = 0;
		i++;
	}
	if (aux_len > cub->map->max_line_len)
		cub->map->max_line_len = aux_len;
}

/**
 * @brief Calcule le nombre de lignes dans le fichier de carte.
 *
 * Cette fonction ouvre le fichier de carte et parcourt ses lignes à l'aide de la fonction
 * `get_next_line`. Pour chaque ligne non vide, il incrémente le membre n_lines dans
 * la structure de données `cub->map`. Après avoir traité toutes les lignes, la fonction ferme
 * le descripteur de fichier et libère les ressources allouées.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 */
void	get_map_n_lines(t_Cub3d *cub)
{
	char	*line;

	cub->map->n_lines = 0;
	cub->map->temp_fd = open(".map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	while (line)
	{
		get_map_n_lines_utils(cub, line, 0, 0);
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	free(line);
	close(cub->map->temp_fd);
}

/**
 * @brief Définit l'orientation du joueur en fonction d'un élément de carte valide.
 *
 * Cette fonction est chargée de définir l'orientation du joueur en fonction d'un caractère d'élément
 * de carte valide ('N', 'S', 'E', 'W'). Il vérifie si le personnage fourni représente une orientation
 * valide et si l'orientation du joueur n'a pas déjà été définie. Si les conditions sont remplies,
 * l'orientation du joueur est mise à jour dans la structure t_Cub3d. Si le caractère n'est pas une orientation
 * valide ou si l'orientation a déjà été définie, la fonction renvoie un code d'erreur.
 *
 * @param cub Pointeur vers la structure t_Cub3d .
 * @param c Le caractère représentant l'élément de la carte.
 * @return Renvoie 0 si l'orientation du joueur est correctement définie, ou 1 si le personnage
 * n'est pas une orientation valide ou si l'orientation est déjà définie.
 */
int	set_player_orientation(t_Cub3d *cub, char c)
{
	char	*charset;

	charset = "01\n\t ";
	if (BONUS)
		charset = "019\n\t ";
	if (ft_strchr("NSEW", c) && !cub->player->orientation)
		cub->player->orientation = c;
	else if (!ft_strchr(charset, c))
		return (1);
	return (0);
}
