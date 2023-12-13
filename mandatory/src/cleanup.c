#include "../headers/cub3d.h"

/**
 * @brief Free ressources allouées pour la carte et les descripteurs de fichiers proches.
 *
 * La fonction 'free_map' est responsable de la libération de la mémoire et des ressources
 * associé aux données map dans Cub3D. Il ferme d'abord le
 * descripteurs de fichier pour le fichier de carte et son compteur temporaire. Ensuite, il
 * itère à travers la matrice contenant les données map et libère la mémoire pour
 * chaque rangée.
 *
 * @param cub Pointer vers la structure 't_Cub3d' contenant le data du programme et
 * données.
 */
static void	free_map(t_Cub3d *cub)
{
	int	i;

	i = 0;
	if (!cub->map->matrix)
		return ;
	while (i <= cub->map->n_lines)
	{
		if (cub->map->matrix[i])
			free(cub->map->matrix[i]);
		i++;
	}
}

/**
 * @brief Free ressources allouées liées à une configuration de texture dans Cub3D
 * demande.
 *
 * La fonction 'free_textures' est responsable de la libération de la mémoire allouée
 * et les ressources associées à une configuration de texture dans Cub3D. Il
 * prend un pointeur vers une structure 't_Cub3d' et un pointeur vers une ' t_TextureSetup`
 * structure comme arguments. La fonction vérifie d'abord si le chemin de texture est
 * alloué et le libère.
 * Il détruit ensuite l'image créée à l'aide de 'mlx_destroy_image' et libère
 * mémoire associée aux données de pixels de l'image. Par la suite
 * la fonction libère la mémoire associée à la structure de contrôle de l'image elle-même.
 * Enfin, la fonction libère la structure de configuration de la texture elle-même. Si le
 * à condition que la structure de texture ou ses attributs soient déjà 'NULL' , la fonction
 * ne tente pas de les libérer.
 *
 * @param cub Pointeur vers la structure 't_Cub3d' contenant le data du programme et
 * données.
 * @param vers pointeur de texture la structure 't_TextureSetup' représentant le
 * texture à libérer.
 */
void	free_textures(t_Cub3d *cub, t_TextureSetup *texture)
{
	if (!texture)
		return ;
	if (texture->path)
		free(texture->path);
	if (texture->img)
	{
		if (texture->img->img_ptr)
			mlx_destroy_image(cub->mlx_ptr, texture->img->img_ptr);
		free(texture->img);
	}
	free(texture);
}

/**
 * @brief Free ressources allouées pour les graphiques et les textures dans Cub3D
 *
 * La fonction` free_graphics ' est responsable de la libération de la mémoire et
 * ressources associées aux graphiques et textures dans Cub3D.
 * Il vérifie si Flag 'graphics_ok' est défini pour s'assurer que les graphiques
 * contexte et les textures ont été initialisés avec succès. Si oui, il procède à
 * libérez les textures des murs nord, sud, ouest et est en utilisant le
 * fonction `free_textures`. Après avoir libéré les textures, il détruit le
 * fenêtre d'application utilisant 'mlx_destroy_window', libère l'affichage, et
 * libère la mémoire allouée pour le contexte MiniLibX.
 *
 * @param cub Pointer vers la structure 't_Cub3d' contenant le data du programme
 * et les données.
 */
static void	free_graphics(t_Cub3d *cub)
{
	free_cam(cub);
	free_gun(cub);
	free_menu(cub);
	if (cub->graphics_ok)
	{
		if (cub->img)
		{
			if (cub->img->img_ptr)
				mlx_destroy_image(cub->mlx_ptr, cub->img->img_ptr);
			free(cub->img);
		}
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
}

/**
 * @brief Désallouer les ressources associées à la minimap dans le jeu Cub3D.
 *
 * La fonction 'free_minimap' est responsable de la libération des mémoire
 * associé à la minimap dans le jeu Cub3D. Il vérifie d'abord si la minimap
 * est initialisé et actif. Si c'est le cas, la fonction procède à la libération de l'image
 * buffer utilisé pour la minimap et la structure de la minimap elle-même. Cela garantit
 * cette mémoire est correctement désallouée lorsqu'elle n'est plus nécessaire.
 *
 * @param cub Pointeur vers la structure de configuration du jeu Cub3D.
 */
static void	free_minimap(t_Cub3d *cub)
{
	if (cub->minimap_ok == false)
		return ;
	if (cub->minimap->img)
	{
		if (cub->minimap->img->img_ptr)
			mlx_destroy_image(cub->mlx_ptr, cub->minimap->img->img_ptr);
		free(cub->minimap->img);
	}
	free(cub->minimap);
}

/**
 * @brief Désallouer les ressources associées à la configuration principale du jeu.
 *
 * La fonction 'free_main' est responsable de la libération de la mémoire et des ressources
 * associé à la configuration principale du jeu dans le jeu Cub3D. Il effectue
 * les actions suivantes:
 *
 * 1. Appelle la fonction` free_minimap ' pour libérer des ressources liées à la
 * minimap.
 * 2. Appelle la fonction` free_graphics ' pour libérer des ressources liées aux graphiques.
 * 3. Appelle la fonction` free_map ' pour libérer de la mémoire liée au jeu
 * map.
 * 4. Vérifie si la structure de la caméra ('cub->cam') est initialisée avec Flag ('cam_ok')
 * et le libère si nécessaire.
 * 5. Vérifie si la matrice représentant la carte du jeu ('cub->map->matrix') est
 * initialisé et le libère si nécessaire.
 * 6. Vérifie si le nom de fichier associé à la carte ('cub->carte->filename') est
 * initialisé et le libère si nécessaire.
 * 7. Vérifie si la structure de joueur ('cub- > player') est initialisée
 * et le libère si nécessaire.
 * 8. Enfin, libère la mémoire associée à la structure de la carte du jeu
 * ('cub->map').
 *
 * @param cub Pointeur vers la structure de configuration principale du jeu Cub3D.
 */
void	free_main(t_Cub3d *cub)
{
	free_minimap(cub);
	free_graphics(cub);
	free_map(cub);
	if (cub->cam_ok)
		free(cub->cam);
	if (cub->map->matrix)
		free(cub->map->matrix);
	if (cub->map->filename)
		free(cub->map->filename);
	if (cub->player)
		free(cub->player);
	if (cub->map)
		free(cub->map);
}