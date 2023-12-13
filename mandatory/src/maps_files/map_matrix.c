#include "../../headers/cub3d.h"

/**
 * @brief Remplissez la matrice de la carte du jeu avec des caractères,
 * en gérant les caractères de nouvelle ligne.
 *
 * La fonction 'fill_matrix3 ' est responsable du remplissage de la matrice
 * de la carte du jeu avec des caractères. Il traite chaque caractère (y compris les
 * caractères de nouvelle ligne) du fichier de carte et les stocke dans les positions appropriées
 * de la matrice.
 *
 * Lorsque vous rencontrez un caractère de nouvelle ligne ('\n'), la fonction s'assure que les positions
 * restantes dans la ligne actuelle de la matrice sont remplies d'espaces (' ') pour aligner correctement
 * la matrice.
 *
 * @param cub Pointeur vers la structure principale du jeu.
 * @param c Le caractère à ajouter à la matrice (y compris '\n ' pour les retours à la ligne).
 * @param y L'index de ligne actuel dans la matrice.
 * @param x Pointeur vers l'index de colonne actuel dans la matrice.
 */
static void	fill_matrix3(t_Cub3d *cub, char c, int y, int *x)
{
	if (c == '\n')
		while (*x < cub->map->max_line_len - 1)
			cub->map->matrix[y][(*x)++] = ' ';
	else
	{
		cub->map->matrix[y][(*x)] = c;
		if (*x < cub->map->max_line_len - 1)
			(*x)++;
	}
}

/**
 * @brief Remplissez la matrice de la carte du jeu avec des données formatées à partir d'une ligne.
 *
 * La fonction 'fill_matrix2' est chargée d'analyser une ligne de données formatées et de remplir
 * la matrice de la carte de jeu en conséquence. Il traite la ligne caractère par caractère, gérant
 * différemment les tabulations et les caractères normaux. Lorsqu'un caractère de tabulation est rencontré,
 * il garantit que le nombre d'espaces correspondant est inséré dans la matrice. Pour les caractères
 * non tabulaires, il délègue la tâche à la fonction 'fill_matrix3' pour gérer le formatage des données
 * de map. Cette fonction est cruciale pour initialiser correctement la carte du jeu pour le rendu.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param line Un pointeur vers la ligne d'entrée contenant les données de la carte.
 * @param y L'index de ligne actuel dans la matrice de la carte.
 * @param x Un pointeur vers l'index de colonne actuel dans la matrice de la carte.
 */
static void	fill_matrix2(t_Cub3d *cub, char *line, int y, int x)
{
	int	i;
	int	tabs;

	i = 0;
	tabs = 0;
	while (line[i])
	{
		tabs++;
		if (line[i] == '\t')
		{
			if (tabs == 8)
				tabs = 0;
			while (tabs++ <= 8)
				cub->map->matrix[y][x++] = ' ';
			tabs = 0;
		}
		else
		{
			if (tabs >= 7)
				tabs = 0;
			fill_matrix3(cub, line[i], y, &x);
		}
		i++;
	}
	cub->map->matrix[y][cub->map->max_line_len - 1] = '\0';
}

/**
 * @brief Remplissez la matrice de map avec les données du fichier .map .
 *
 * Cette fonction lit le fichier de carte ligne par ligne à l'aide de la fonction get_next_line
 * et remplit la structure de données cub->map->matrix avec les caractères du fichier de carte.
 * Il alloue de la mémoire pour chaque ligne de la matrice et appelle la fonction fill_matrix2
 * pour traiter chaque caractère de la ligne et remplir les positions correspondantes de la matrice.
 * Après avoir traité chaque ligne, il incrémente l'index de ligne et libère la mémoire allouée.
 *
 * @param cub Pointeur vers la structure t_Cub3d .
 * @return Renvoie 0 si la matrice est remplie avec succès, ou 1 dans le cas d'un
 * erreur.
 */
int	fill_matrix(t_Cub3d *cub)
{
	int		y;
	char	*line;

	y = 0;
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return (1);
	cub->map->matrix = ft_calloc(cub->map->n_lines + 1, sizeof(char *));
	while (line)
	{
		cub->map->matrix[y] = ft_calloc(cub->map->max_line_len + 1,
				sizeof(char));
		fill_matrix2(cub, line, y, 0);
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
	return (free(line), close(cub->map->temp_fd), 0);
}