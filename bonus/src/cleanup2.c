#include "../headers/cub3d.h"

/**
 * @brief Désallouer les ressources associées au menu du jeu dans Cub3D.
 *
 * La fonction 'free_menu' est responsable de la libération de la mémoire et des ressources
 * associé au menu du jeu dans le jeu Cub3D. Il vérifie si le menu
 * est actif avec le Flag ('menu_ok') et libère toutes les textures utilisées par le
 * menu, comme les boutons 'start' et 'quit'. Enfin, il libère la mémoire allouée
 * pour la structure du menu et définit le Flag 'menu_active' sur false, indiquant
 * que le menu n'est plus utilisé.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	free_menu(t_Cub3d *cub)
{
	if (cub->menu_ok)
	{
		if (cub->main->start)
			free_textures(cub, cub->main->start);
		if (cub->main->quit)
			free_textures(cub, cub->main->quit);
		free(cub->main);
	}
	cub->menu_active = false;
}

/**
 * @brief Désallouer les ressources associées au gun et au crosshair du joueur.
 *
 * La fonction 'free_gun' est responsable de la libération de la mémoire et des ressources
 * associé au gun et au crosshair du joueur dans le jeu Cub3D. Il vérifie
 * si ces ressources sont initialisées Flag ('gun_ok') et se libèrent
 * toutes les textures utilisées pour le gun et le crosshair. Cela garantit que la mémoire est
 * correctement libéré lorsque ces éléments ne sont plus nécessaires.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	free_gun(t_Cub3d *cub)
{
	if (cub->gun_ok)
	{
		if (cub->player->gun)
			free_textures(cub, cub->player->gun);
		if (cub->player->crosshair)
			free_textures(cub, cub->player->crosshair);
	}
}

/**
 * @brief Désallouer les ressources associées aux textures de la caméra et
 * configurations.
 *
 * La fonction ('free_cam') est responsable de la libération de la mémoire et des ressources
 * associé aux textures et configurations de caméra dans le jeu Cub3D. Il
 * libère de la mémoire allouée pour diverses textures, y compris nord, sud,
 * textures ouest et est, ainsi que des textures de porte en cas de bonus.
 * Si les ressources liées aux fichiers sont initialisées Flag ('files_ok'), cela libère le
 * mémoire utilisée pour les textures stockées dans la structure de la caméra. Enfin, le
 * la fonction libère la mémoire allouée pour le tableau de textures de la caméra et d'autres
 * data.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
void	free_cam(t_Cub3d *cub)
{
	int	i;

	i = 0;
	if (cub->map->tex_north)
		free_textures(cub, cub->map->tex_north);
	if (cub->map->tex_south)
		free_textures(cub, cub->map->tex_south);
	if (cub->map->tex_west)
		free_textures(cub, cub->map->tex_west);
	if (cub->map->tex_east)
		free_textures(cub, cub->map->tex_east);
	if (BONUS && cub->map->tex_door)
		free_textures(cub, cub->map->tex_door);
	if (cub->files_ok)
	{
		while (i < 4 + BONUS)
		{
			if (cub->cam->tex[i])
				free(cub->cam->tex[i]);
			i++;
		}
		free(cub->cam->tex);
	}
}