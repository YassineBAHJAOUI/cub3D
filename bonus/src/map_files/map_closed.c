#include "../../headers/cub3d.h"

/**
 * @brief Vérifiez si les limites supérieure et inférieure de la carte sont fermées.
 *
 * Cette fonction vérifie si les limites supérieure et inférieure de la carte sont
 * correctement fermées, en s'assurant que tous les éléments le long de ces limites
 * sont soit '1' (mur), soit un espace vide ' '. Si d'autres caractères sont trouvés
 * le long de ces limites, la fonction renvoie 1 pour indiquer une erreur.
 * Sinon, il renvoie 0 pour indiquer une validation réussie.
 *
 * Pointeur @ param cub vers la structure t_Cub3d contenant le contexte et les données du programme.
 * @return Renvoie 0 si les limites supérieure et inférieure sont correctement fermées, ou 1 si une erreur est détectée.
 */
static int	check_top_bot_closed(t_MapConfig *m)
{
	int	i;
	int	last_row;

	i = 0;
	last_row = m->n_lines;
	while (m->matrix[0][i])
	{
		if (!ft_strchr("1 ", m->matrix[0][i]))
			return (1);
		i++;
	}
	i = 0;
	while (m->matrix[last_row][i])
	{
		if (!ft_strchr("1 ", m->matrix[last_row][i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Vérifie l'environnement d'un personnage dans la matrice de la carte.
 *
 * La fonction 'check_surroundings' examine les caractères voisins d'un personnage
 * spécifique dans la matrice de la carte du jeu. Il vérifie si le personnage respecte
 * les règles d'une disposition de carte valide, y compris les murs, les portes
 * et les espaces vides. Si des incohérences ou des erreurs sont détectées dans
 * l'environnement, la fonction renvoie un code d'erreur.
 *
 * @param m Pointeur vers la configuration de la carte.
 * @param i L'index de ligne du caractère à vérifier.
 * @param j L'index de colonne du caractère à vérifier.
 * @return Renvoie 1 si les environs sont invalides, 0 s'ils sont valides.
 */
int	check_surroundings(t_MapConfig *m, int i, int j)
{
	char	*charset;

	charset = "0NSEW";
	if (BONUS)
		charset = "09NSEW";
	if ('1' == m->matrix[i][j])
		return (0);
	else if (ft_strchr(charset, m->matrix[i][j]))
	{
		if (j == 0 && (m->matrix[i][j] != '1' || m->matrix[i][j] != ' '))
			return (1);
		if (get_matrix_borders(m, i, j))
			return (1);
		if ((m->up_valid && m->matrix[i - 1][j] == ' ')
			|| (m->down_valid && m->matrix[i + 1][j] == ' ')
			|| (m->left_valid && m->matrix[i][j - 1] == ' ')
			|| (m->right_valid && m->matrix[i][j + 1] == ' '))
			return (1);
		if (check_walls_doors(m, i, j))
			return (1);
	}
	else if (ft_strchr("\n\t ", m->matrix[i][j]))
		return (0);
	return (0);
}

/**
 * @brief Vérifiez l'espace blanc non valide entre les murs de la carte.
 *
 * Cette fonction vérifie la présence d'espaces blancs non valides entre
 * les murs dans la matrice de la carte. Il examine si un espace (' ') est
 * rencontré et vérifie si l'élément à sa gauche est '0', indiquant un espace
 * vide entre les murs. De tels espaces vides peuvent entraîner une disposition
 * de carte non fermée. Si les deux conditions sont remplies, la fonction renvoie
 * 1 pour indiquer une erreur.
 *
 * La fonction gère également le passage à la ligne suivante de la matrice si la fin
 * de la ligne est atteinte (lorsque j est égal à la longueur maximale de la ligne),
 * mettant à jour l'index de ligne (*i) et réinitialisant l'index de colonne (j) en conséquence.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @param i pointe vers l'index de ligne actuel dans la matrice.
 * @param j Indice de colonne actuel dans la matrice.
 * @return Renvoie 1 si un espace blanc non valide entre les murs est trouvé, ou 0 sinon.
 */
static int	check_nullb_whitespaces(t_MapConfig *m, int *i, int *j)
{
	if (*j == m->max_line_len)
		return ((*i)++, *j = 0, 0);
	if (ft_strchr(" ", m->matrix[*i][*j]) && *j == 0)
		return (0);
	if (ft_strchr(" ", m->matrix[*i][*j])
		&& ft_strchr("09", m->matrix[*i][*j - 1]))
		return (1);
	return (0);
}

/**
 * @brief Vérifiez la validité des placements de porte sur la carte.
 *
 * La fonction 'check_closed' scanne la matrice de la carte pour vérifier si
 * le placement des portes est valide. Il vérifie si les portes ont l'une des
 * deux configurations spécifiques: un chemin disponible du nord au sud tout en
 * ayant des murs sur les côtés est et ouest, ou des murs sur les côtés nord et
 * sud avec un chemin vers l'est et l'ouest. Si ces conditions ne sont pas remplies,
 * la fonction renvoie un code d'erreur, indiquant un placement de porte non valide.
 *
 * @ param m Pointeur vers la structure de configuration de la carte.
 * @param i L'index de ligne du caractère courant.
 * @param j L'index de colonne du caractère courant.
 * @return Renvoie 1 si l'emplacement de la porte n'est pas valide, 0 s'il est valide.
 */
static int	check_closed(t_MapConfig *m, int i, int j)
{
	char	*charset;

	charset = "0NSEW";
	if (BONUS)
		charset = "09NSEW";
	while (i <= m->n_lines - 1)
	{
		j = 0;
		while (j <= m->max_line_len - 1)
		{
			if (check_nullb_whitespaces(m, &i, &j))
				return (1);
			if (i > m->n_lines)
				break ;
			if (check_surroundings_utils(m, i, j, charset))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Vérifiez l'enceinte de la carte et les zones de mouvement des joueurs valides.
 *
 * Cette fonction vérifie si la carte est entourée de murs et comporte des zones de mouvement
 * valides pour les joueurs. Il utilise les fonctions 'check_top_bot_closed' et 'check_closed'
 * pour ces vérifications.
 *
 * @param cub Pointeur vers la structure t_Cub3d.
 * @return Renvoie 1 si la carte n'est pas incluse ou comporte des zones de déplacement non valides,
 * sinon renvoie 0.
 */
int	check_map_closed(t_Cub3d *cub)
{
	if (check_top_bot_closed(cub->map) || check_closed(cub->map, 1, 0))
		return (1);
	return (0);
}
