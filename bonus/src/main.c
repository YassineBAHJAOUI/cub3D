#include "../headers/cub3d.h"

/**
 * @brief Gère l'événement de fermeture de la fenêtre dans le jeu Cub3D.
 *
 * La fonction win_close est responsable de la gestion de l'événement de fermeture de 
 * fenêtre dans l'application Cub3D. Lorsqu'il est déclenché, il effectue des opérations
 * de nettoyage en appelant la fonction free_main pour libérer les ressources allouées
 * et assurer un arrêt propre de l'application. De plus, il affiche un message indiquant
 * la fermeture de jeu. Le paramètre 'false' passé à la fonction d'arrêt indique que jeu
 * doit se terminer avec un statut réussi (EXIT_SUCCESS), l'empêchant de planter en raison
 * d'erreurs.
 *
 * @param cub Pointeur vers la structure t_Cub3d contenant les données du programme.
 */
int	win_close(t_Cub3d *cub)
{
	free_main(cub);
	printf("Closing CUB3D\n");
	exit(EXIT_SUCCESS);
}

/**
* @brief Initialise le programme et ses composants.
*
* La fonction d'initialisation est responsable de la configuration initiale
* état du programme. Il effectue les tâches suivantes:
*
* 1. Vérifie le nombre d'arguments de ligne de commande et valide l'entrée.
* 2. Initialise les paramètres de la carte en analysant le fichier de carte fourni.
* 3. Tente d'initialiser le sous-système graphique à l'aide de MiniLibX.
* 4. Gère les erreurs et arrête gracieusement le programme en cas d'échec.
*
* @param ac Le nombre d'arguments de ligne de commande.
* @param av Un tableau de chaînes représentant les arguments de la ligne de commande.
* @param cub Pointeur vers la structure t_Cub3d qui contient les données du programme.
*/
static void	initialization(int ac, char **av, t_Cub3d *cub)
{
	if (ac != 2)
	{
		printf("Error: Please input exactly two arguments\n");
		exit(EXIT_FAILURE);
	}
	if (map_init(cub, av[1]))
	{
		free_main(cub);
		printf("Error: Failed initializing map settings\n");
		exit(EXIT_FAILURE);
	}
	if (graphics(cub))
	{
		free_main(cub);
		printf("Error: Failed booting graphics.\n");
		printf("\tPlease check MiniLibX is installed on your system\n");
		printf("\tPlease check the texture files, so they are XPM\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Gérer les interactions avec le menu du jeu.
 *
 * Cette fonction vérifie si le curseur de la souris est sur les boutons "Start" et "Quit",
 * met à jour leur apparence et revient.
 *
 * @param cub Pointeur vers la configuration principale du jeu Cub3D.
 */
static void	menu_loop(t_Cub3d *cub)
{
	int	start;
	int	quit;

	start = button_mo(cub, cub->main->start->img, 's');
	quit = button_mo(cub, cub->main->quit->img, 'q');
	update_button(cub, cub->main->start->img, start, 's');
	update_button(cub, cub->main->quit->img, quit, 'q');
}

/**
 * @brief Main gameloop responsable de la logique et du rendu du jeu.
 *
 * La fonction "gameloop" est le cœur de la boucle de jeu Cub3D.
 * Il effectue les actions suivantes:
 * 1. Si le menu du jeu est actif ('cub- > menu_active') est vrai,
 * il appelle la fonction 'menu_loop' pour gérer les interactions et
 * les mises à jour du menu.
 * 2. Si le menu n'est pas actif, il procède à la logique principale
 * du jeu et au rendu:
 *		- Appelle la fonction 'readmove' pour gérer les mouvements du joueur.
 *		- Restaure les portes à leur état d'origine (le cas échéant) en utilisant
 * la fonction restore_doors. Cette fonction semble s'occuper de la restauration
 * de l'état du jeu.
 *		- Appelle 'cub3d_new_image' pour créer une nouvelle image pour la fenêtre
 * principale du jeu.
 *		- Appelle 'minimap_new_image' pour créer une nouvelle image pour la minimap.
 *		- Dessine la minimap en utilisant la fonction 'draw_minimap'.
 *		- Exécute le lancer de rayons et dessine la scène du jeu à l'aide
 * de la fonction ('draw_rays').
 *		- Rend l'arme du joueur en utilisant la fonction 'draw_gun'.
 *		- Rend le crosshair en utilisant la fonction 'draw_crosshair'.
 * 		- Place l'image principale du jeu et l'image de la minimap dans la fenêtre
 * du jeu à l'aide de la fonction `mlx_put_image_to_window`.
 * 		- Vérifie si le joueur tire ('cub->player->shoot') et met à jour l'animation
 * du pistolet à l'aide de la fonction 'shoot_gun'.
 * 		- Désactive le menu du jeu (`cub->menu_active = false`) après le rendu.
 * 		- Si le joueur tire, il incrémente le compteur " pistolet`.
 *
 * @param cub Pointeur vers la structure de configuration principale du jeu Cub3D.
 * @return renvoie toujours 0.
 */
int	gameloop(t_Cub3d *cub)
{
	static int	gun;

	if (cub->menu_active)
	{
		menu_loop(cub);
		return (0);
	}
	readmove(cub, cub->player);
	restore_doors(cub, 0, 0, 0);
	cub3d_new_image(cub);
	minimap_new_image(cub);
	draw_minimap(cub);
	draw_rays(cub);
	draw_gun(cub, cub->player, 0, 0);
	draw_crosshair(cub, cub->player, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->img->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,
		cub->minimap->img->img_ptr, 30, 30);
	if (cub->player->shoot)
		shoot_gun(cub, cub->player, &gun);
	cub->menu_active = false;
	if (cub->player->shoot)
		gun++;
	return (0);
}

/**
 * Use mlx_mouse_hide(cub.mlx_ptr, cub.win_ptr) if you want
 * to hide the mouse.
 */
int	main(int ac, char **av, char **env)
{
	t_Cub3d	cub;

	(void)env;
	cub.graphics_ok = false;
	cub.files_ok = false;
	cub.menu_active = false;
	cub.minimap_ok = false;
	cub.menu_ok = false;
	cub.cam_ok = false;
	cub.gun_ok = false;
	initialization(ac, av, &cub);
	mlx_mouse_move(cub.mlx_ptr, cub.win_ptr, WINDOW_X / 2, WINDOW_Y / 2);
	mlx_mouse_get_pos(cub.mlx_ptr, cub.win_ptr, &cub.mouse_x, &cub.mouse_y);
	hook_events(&cub);
	mlx_loop_hook(cub.mlx_ptr, &gameloop, &cub);
	mlx_loop(cub.mlx_ptr);
	free_main(&cub);
	printf("Closing CUB3D\n");
	return (0);
}