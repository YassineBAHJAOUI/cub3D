#include "../../headers/cub3d.h"

/**
 * @brief Vérifiez l'environnement d'un personnage spécifié sur la carte.
 *
 * La fonction 'check_surroundings_utils' examine les tuiles environnantes
 * d'un caractère spécifié dans la matrice de la carte pour vérifier qu'elle est
 * placée dans un contexte valide. Il est généralement utilisé pour vérifier si des
 * caractères tels que '0', 'N', 'S', 'W' et 'E' ont des tuiles voisines appropriées,
 * telles que des murs ou d'autres caractères valides.
 * Si l'environnement n'est pas valide, la fonction renvoie une erreur.
 *
 * @ param m Pointeur vers la configuration de la carte.
 * @param i L'index de ligne du caractère.
 * @param j L'index de la colonne du caractère.
 * @param charset Une chaîne contenant des caractères valides pour l'environnement.
 * @return Renvoie 1 si les environs sont invalides, 0 s'ils sont valides.
 */
int	check_surroundings_utils(t_MapConfig *m, int i, int j, char *charset)
{
	if ('1' == m->matrix[i][j])
	{
		if (check_surroundings(m, i, j))
			return (1);
	}
	else if (ft_strchr(charset, m->matrix[i][j])
		&& m->matrix[i][j])
	{
		if (check_surroundings(m, i, j))
			return (1);
	}
	return (0);
}
