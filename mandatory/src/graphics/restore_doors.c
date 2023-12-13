#include "../../headers/cub3d.h"

/**
 * @brief Restaure une porte dans la matrice de la carte.
 *
 * La fonction 'restore' vérifie si la position spécifiée dans la matrice de
 * la carte contient un '0' et si la position du joueur est suffisamment éloignée
 * de celle-ci. Si ces conditions sont remplies, il modifie la valeur de la carte à
 * '9', rétablissant effectivement cette position.
 *
 * @param cub Pointeur vers la structure de configuration principale du jeu Cub3D.
 * @param x La coordonnée x dans la matrice de la carte.
 * @param y La coordonnée y dans la matrice de la carte.
 */
static void	restore(t_Cub3d *cub, int x, int y)
{
	if (cub->map->matrix[y][x] == '0'
		&& (cub->player->pos_y > y + 3 || cub->player->pos_y < y - 3
			|| cub->player->pos_x > x + 3
			|| cub->player->pos_x < x - 3))
		cub->map->matrix[y][x] = '9';
}

/**
 * @brief Compter les onglets dans une ligne et calculer la position horizontale.
 *
 * La fonction 'count_tabs' compte le nombre d'onglets dans une ligne et calcule la position
 * horizontale (x) en fonction du nombre d'onglets. Il réinitialise également le nombre de
 * tabulations à 0 après le traitement des tabulations. Cette fonction est généralement utilisée
 * pour suivre les positions horizontales dans une ligne contenant des onglets.
 *
 * @param line Une chaîne représentant une ligne de texte.
 * @param i L'index courant dans la ligne.
 * @param tabs Un pointeur vers un entier stockant le nombre de tabulations.
 * @return la position horizontale (x) calculée en fonction du nombre de tabulations.
 */
static int	count_tabs(char *line, int i, int *tabs)
{
	int	x;

	x = 0;
	(*tabs)++;
	if (line[i] == '\t')
	{
		if (*tabs == 7)
			(*tabs) = 0;
		while (*tabs < 8)
		{
			x++;
			(*tabs)++;
		}
		*tabs = 0;
	}
	else if (*tabs == 7)
		(*tabs) = 0;
	return (x);
}

/**
 * @brief Vérifie si l'emplacement d'une tuile de porte sur la carte est valide.
 *
 * La fonction 'check_walls_doors' examine la configuration de la carte pour déterminer
 * si une tuile de porte ('9') est correctement placée. En mode bonus, les tuiles de porte
 * doivent avoir un environnement spécifique pour être considérées comme valides:
 * soit des murs à l'ouest (W) et à l'est (E) avec des chemins piétonniers au nord (N) et au sud (S),
 * soit des murs au nord (N) et au sud (S) avec des chemins piétonniers à l'ouest (W) et à l'est (E).
 * Si aucune de ces conditions n'est remplie, la fonction renvoie 1, indiquant un placement de porte
 * invalide, sinon elle renvoie 0, signifiant un placement de porte valide.
 *
 * @param m Pointeur vers la structure de configuration t_Map contenant les données de la carte.
 * @param i L'index de ligne de la tuile de porte.
 * @param j L'index de la colonne de la tuile de porte.
 * @return 0 si le placement des carreaux de porte est valide, 1 s'il n'est pas valide.
 */
int	check_walls_doors(t_MapConfig *m, int i, int j)
{
	if (m->matrix[i][j] == '9')
	{
		if (BONUS)
		{
			if ((m->matrix[i][j - 1] == '0'
				|| ft_strchr("NSEW", m->matrix[i][j - 1]))
				&& (m->matrix[i][j + 1] == '0'
				|| ft_strchr("NSEW", m->matrix[i][j + 1]))
				&& m->matrix[i - 1][j] == '1' && m->matrix[i + 1][j] == '1')
				return (0);
			else if (m->matrix[i][j - 1] == '1' && m->matrix[i][j + 1] == '1'
				&& (m->matrix[i - 1][j] == '0'
				|| ft_strchr("NSEW", m->matrix[i - 1][j]))
				&& (m->matrix[i + 1][j] == '0'
				|| ft_strchr("NSEW", m->matrix[i + 1][j])))
				return (0);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

/**
 * @brief Restaure les tuiles de porte sur la carte si des conditions spécifiques sont remplies.
 *
 * La fonction 'restore_doors' scanne la carte à la recherche de tuiles de porte ('9')
 * et les restaure à leur état d'origine sous certaines conditions. Une porte peut être
 * restaurée si elle a déjà été ouverte ('0') et que le personnage joueur n'est pas à proximité.
 * La fonction lit les données cartographiques à partir d'un fichier temporaire et vérifie l'éligibilité
 * de chaque carreau de porte à la restauration.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param x La coordonnée x initiale pour scanner la carte.
 * @param y La coordonnée y initiale pour scanner la carte.
 */
void	restore_doors(t_Cub3d *cub, int x, int y, int i)
{
	char	*line;
	int		tabs;

	tabs = 0;
	cub->map->temp_fd = open("./.map", O_RDONLY);
	line = get_next_line(cub->map->temp_fd);
	if (!line)
		return ;
	while (line)
	{
		x = 0;
		i = 0;
		tabs = 0;
		while (line[i])
		{
			x += count_tabs(line, i, &tabs);
			if (line[i] == '9')
				restore(cub, x, y);
			x++;
			i++;
		}
		y++;
		free(line);
		line = get_next_line(cub->map->temp_fd);
	}
}