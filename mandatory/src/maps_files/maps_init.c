#include "../../headers/cub3d.h"

/**
 * @brief Initialise les configurations de texture pour la carte du jeu.
 *
 * La fonction ('tex_init') est responsable de l'initialisation de la texture
 * configurations pour différentes directions (nord, sud, ouest et est) dans le
 * carte du jeu. Ces textures sont essentielles pour le rendu de l'environnement de jeu.
 * De plus, si les fonctionnalités bonus sont activées, il initialise également une porte
 * texture.
 *
 * Si un échec d'allocation se produit pendant le processus d'initialisation, le
 * la fonction libère la mémoire précédemment allouée, affiche un message d'erreur et
 * terminer le programme.
 *
 * @param cub Pointeur vers la structure principale du jeu.
 */
static void	tex_init(t_Cub3d *cub)
{
	cub->map->tex_north = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_south = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_west = ft_calloc(1, sizeof(t_TextureSetup));
	cub->map->tex_east = ft_calloc(1, sizeof(t_TextureSetup));
	if (!cub->map->tex_north || !cub->map->tex_south
		|| !cub->map->tex_west || !cub->map->tex_east)
	{
		free_main(cub);
		printf("Error: fatal: t_TextureSetup not created\n");
		exit(EXIT_FAILURE);
	}
	if (BONUS)
	{
		cub->map->tex_door = ft_calloc(1, sizeof(t_TextureSetup));
		if (!cub->map->tex_door)
		{
			free_main(cub);
			printf("Error: fatal: tex_door not created\n");
			exit(EXIT_FAILURE);
		}
	}
	cub->map->colors[0] = false;
	cub->map->colors[1] = false;
}

/**
 * @brief Initialise la configuration et les données de la carte dans le contexte Cub3D.
 *
 * Cette fonction initialise la configuration et les données de la carte dans Cub3D.
 * Il alloue de la mémoire pour une structure 't_MapConfig' et initialise ses membres.
 * La fonction met le compteur de sauts à 0 et duplique le nom de fichier fourni.
 * Si l'allocation de mémoire échoue, la fonction appelle `free_main ' pour nettoyer les
 * ressources allouées et termine le programme avec un message d'erreur.
 *
 * La fonction initialise ensuite la configuration de la texture à l'aide de la fonction `tex_init`.
 * Il procède à l'analyse du fichier de la carte à l'aide de la fonction 'parse_map_file' et
 * remplit la matrice de la carte à l'aide de la fonction `fill_matrix`. Enfin, il vérifie si
 * la carte est correctement entourée de murs et comporte des zones de mouvement de joueur valides
 * à l'aide de la fonction `check_map_closed`. Si une étape rencontre une erreur, la fonction
 * renvoie 1, sinon elle renvoie 0 pour indiquer une initialisation réussie.
 *
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @param file Nom du fichier de la carte à analyser.
 * @return Renvoie 1 si une étape d'initialisation échoue, sinon renvoie 0.
 */

int	map_init(t_Cub3d *cub, char *file)
{
	cub->map = ft_calloc(1, sizeof(t_MapConfig));
	if (!cub->map)
	{
		free_main(cub);
		printf("Error: fatal: t_MapConfig not created\n");
		exit(EXIT_FAILURE);
	}
	cub->map->skip_counter = 0;
	cub->map->max_line_len = 0;
	cub->map->filename = ft_strdup(file);
	tex_init(cub);
	if (player_init(cub))
	{
		free_main(cub);
		printf("Error: Failed initializing player settings\n");
		exit(EXIT_FAILURE);
	}
	parse_map_file(cub);
	if (fill_matrix(cub))
		return (printf("Error: failed creating matrix\n"), 1);
	if (check_map_closed(cub))
		return (printf("Error: map isn't closed off\n"), 1);
	return (0);
}