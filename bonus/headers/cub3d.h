#ifndef CUB3D_H
# define CUB3D_H

# include "../../mlx/mlx.h"
# include "../../mlx/mlx_int.h"
# include "constants.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>

/**
 * @struct t_WindowConfig
 * Structure de configuration des propriétés de la fenêtre dans le projet Cub3D.
 * Il définit les dimensions et les proportions de la fenêtre de rendu du jeu.
 *
 * @param WindowSizeX Largeur de la fenêtre de rendu en pixels.
 * @param WindowSizeY Hauteur de la fenêtre de rendu en pixels.
 * @param WindowAspectRatio hauteur / largeur de la fenêtre.
 */
typedef struct s_WindowConfig
{
	int	width;
	int	height;
	int	aspect_ratio;
}				t_WindowConfig;

/**
 * @struct t_ImageControl
 * @brief Structure de gestion des données et propriétés d'image dans Cub3D
 * projet.
 *
 * La structure de t_ImageControl permet de contrôler diverses images liées
 * attributs requis pour le rendu dans le projet Cub3D.
 *
 * @param img_ptr Un pointeur sur les données de pixels de l'image.
 * @param addr Un pointeur de caractère vers le début des données de pixels de l'image.
 * @param bpp Bits par pixel pour l'image.
 * @param len Longueur de chaque ligne d'image en octets.
 * @param endian  L'ordre des octets dans les données d'image (endianess).
 * @param width  Largeur de l'image en pixels.
 * @param height Hauteur de l'image en pixels.
 */
typedef struct s_ImageControl
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;
}				t_ImageControl;

/**
 * @struct t_TextureSetup
 * Structure de gestion de la configuration des textures dans le projet Cub3D.
 *
 * Cette structure contient des données relatives aux chemins de texture et aux images.
 *
 * @param path Chemin d'accès au fichier de texture.
 * @param img Pointeur vers la structure de contrôle de l'image.
 */
typedef struct s_TextureSetup
{
	char			*path;
	t_ImageControl	*img;
}				t_TextureSetup;

/**
 * @struct t_PlayerConfig
 * Structure de gestion de la configuration et de l'état des joueurs dans le jeu.
 *
 * Cette structure contient des données relatives à la position et à l'orientation du joueur,
 * Contrôles d'entrée et divers attributs de jeu.
 *
 * @param orientation L'orientation ou la direction du joueur.
 * @param pos_x Coordonnée X de la position du joueur dans l'espace 2D.
 * @param pos_y Coordonnée Y de la position du joueur dans l'espace 2D..
 * @param dir_x X-composante du vecteur de direction opposé du joueur.
 * @param dir_y Y-composante du vecteur de direction opposé du joueur.
 * @param up Flag indiquant si le contrôle de mouvement "up" est actif.
 * @param down Flag indiquant si le contrôle de mouvement "down" est actif.
 * @param left Flag indiquant si le contrôle de mouvement "left" est actif.
 * @param right Flag indiquant si le contrôle de mouvement "right" est actif.
 * @param l_key État de la touche gauche ou de l'action.
 * @param r_key État de la touche droite ou de l'action.
 * @param shoot shoot indiquant si le joueur est en train de tirer.
 * @param use_distance_y Y-coordonnée pour l'utilisation ou l'interaction avec les objets.
 * @param use_distance_x X-coordonnée pour l'utilisation ou l'interaction avec les objets.
 * @param crosshair Pointeur vers la configuration de la texture du réticule.
 * @param gun Pointer vers la configuration de la texture du pistolet.
 */
typedef struct s_PlayerConfig
{
	char			orientation;
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	int				up;
	int				down;
	int				left;
	int				right;
	int				l_key;
	int				r_key;
	int				shoot;
	float			use_distance_y;
	float			use_distance_x;
	t_TextureSetup	*crosshair;
	t_TextureSetup	*gun;
}				t_PlayerConfig;

/**
 * @struct t_MiniMap
 * Structure de gestion de la mini-carte dans le jeu Cub3D.
 *
 *  La mini-carte fournit une représentation réduite du monde du jeu pour
 * aidez les joueurs à naviguer et à acquérir une conscience de la situation.
 *
 * @param img Pointer vers la structure de contrôle de l'image pour la mini-carte.
 * @param width Largeur de l'image de la minicarte.
 * @param height Hauteur de l'image de la minicarte.
 * @param draw_x Coordonnée X pour dessiner sur l'image de la mini-carte.
 * @param draw_y Coordonnée Y pour dessiner sur l'image de la mini-carte.
 * @param player_x Coordonnée X de la position du joueur sur la minicarte.
 * @param player_y Coordonnée Y de la position du joueur sur la minicarte.
 * @param flag flag utilisé pour déterminer l'état ou le comportement de la minicarte.
 */
typedef struct s_MiniMap
{
	t_ImageControl	*img;
	int				width;
	int				height;
	int				draw_x;
	int				draw_y;
	int				player_x;
	int				player_y;
	int				flag;
}				t_MiniMap;

/**
 * @struct t_MapConfig
 * Structure de gestion de la configuration de la carte dans le jeu Cub3D.
 *
 * La structure 't_MapConfig' contient divers paramètres et données liés à la
 * carte du jeu, y compris les descripteurs de fichiers, les dimensions de la carte, la représentation matricielle,
 * couleurs et configurations de texture.
 *
 * @param fd Descripteur de fichier pour le fichier de carte.
 * @param temp_fd Descripteur de fichier temporaire pour les opérations de fichier de carte.
 * @param n_lines Nombre de lignes sur la carte.
 * @param max_line_len Longueur maximale d'une ligne sur la carte.
 * @param skip_counter Un compteur utilisé pour analyser la carte.
 * @param matrix Représentation matricielle de la carte.
 * @param up_valid Flag indiquant si "up" est valide dans une position donnée.
 * @param down_valid Flag indiquant si le "down" est valide dans une position donnée.
 * @param left_valid Flag indiquant si le "left" est valide dans une position donnée.
 * @param right_valid Flag indiquant si le "right" est valide dans une position donnée.
 * @param filename Nom du fichier de la carte.
 * @param floor_c  Valeurs de couleur pour le sol.
 * @param ceilling_c Valeurs de couleur pour le plafond.
 * @param colors Flags indiquant si les couleurs du sol et du plafond ont été définies
 * @param tex_north  Configuration de texture pour le mur orienté au nord.
 * @param tex_south  Configuration de texture pour le mur orienté au sud.
 * @param tex_east  Configuration de texture pour le mur orienté au est.
 * @param tex_west  Configuration de texture pour le mur orienté au ouest.
 * @param tex_door Configuration de texture pour les portes (si disponible, pour bonus).
 * @param door_pos Positions des portes sur la carte (si disponible, pour le bonus).
 */
typedef struct s_MapConfig
{
	int				fd;
	int				temp_fd;
	int				n_lines;
	int				max_line_len;
	int				skip_counter;
	char			**matrix;
	int				up_valid;
	int				down_valid;
	int				left_valid;
	int				right_valid;
	char			*filename;
	int				floor_c[256][256][256];
	int				ceilling_c[256][256][256];
	bool			colors[2];
	t_TextureSetup	*tex_north;
	t_TextureSetup	*tex_south;
	t_TextureSetup	*tex_east;
	t_TextureSetup	*tex_west;
	t_TextureSetup	*tex_door;
	char			**door_pos;
}				t_MapConfig;

/**
 * @struct t_Transform
 * Structure pour représenter les transformations 3D dans l'espace.
 *
 *  La structure 't_Transform' contient trois valeurs de double précision
 * (`x`,` y `et` z') représentant des coordonnées 3D ou des transformations dans l'espace.
 *
 * @param x La coordonnée x
 * @param y La coordonnée y
 * @param z La coordonnée z
 */
typedef struct s_Transform
{
	double	x;
	double	y;
	double	z;
}				t_Transform;

/**
 * @struct t_CameraConfig
 * Structure de gestion de la configuration de la caméra dans le projet Cub3D.
 *
 * La structure 't_CameraConfig' contient divers paramètres et données liés à
 * la caméra utilisée pour le rendu des scènes dans le projet Cub3D.
 *
 * @param fov Angle du champ de vision (FOV) en radians.
 * @param camera_x Cordonnée X de la position de la caméra.
 * @param plane_x Cordonnée X du plan de vue de la caméra.
 * @param plane_y Cordonnée Y du plan de vue de la caméra.
 * @param raydir_x Cordonnée X de la direction actuelle du rayon.
 * @param raydir_y Cordonnée Y de la direction actuelle du rayon.
 * @param olddir_x Cordonnée X de la direction du rayon précédent.
 * @param oldplane_x Cordonnée X du plan de vue précédent.
 * @param map_x Cordonnée X de la cellule de grille de carte actuelle.
 * @param map_y Cordonnée Y de la cellule de grille de carte actuelle.
 * @param ddist_x Distance Delta entre les coordonnées X de la position actuelle et suivante
 * cartographier les cellules de la grille.
 * @param ddist_y Distance Delta entre les coordonnées Y de la position actuelle et suivante
 * cartographier les cellules de la grille.
 * @param s_dist_x Distance latérale à la prochaine limite de cellule de la grille de coordonnées X.
 * @param s_dist_y Distance latérale à la prochaine limite de cellule de la grille de coordonnées Y.
 * @param perp_wd Distance perpendiculaire du mur par rapport à la caméra.
 * @param camera_rot Angle de rotation actuel de la caméra.
 * @param step_x Valeur de pas pour la coordonnée X dans le lancer de rayons.
 * @param step_y Valeur de pas pour la coordonnée Y dans le lancer de rayons.
 * @param hit Flag indiquant si un mur a été touché.
 * @param side Flag indiquant de quel côté du mur a été touché (0 pour vertical, 1
 * pour horizontal).
 * @param line_height Hauteur de la ligne de mur à dessiner.
 * @param draw_start Position de départ du pixel pour dessiner le mur.
 * @param draw_end Position du pixel de fin pour dessiner le mur.
 * @param wall_dir Direction du mur (Nord, Sud, Est ou Ouest).
 * @param wallhit Distance au coup de mur.
 * @param tex_x Coordonnée X de la texture échantillonnée.
 * @param tex_y Coordonnée Y de la texture échantillonnée.
 * @param tex_w Largeur de la texture actuellement sélectionnée.
 * @param tex_h Hauteur de la texture actuellement sélectionnée.
 * @param tex_step Taille de pas pour l'échantillonnage de texture.
 * @param tex_pos Position d'échantillonnage de texture actuelle.
 * @param tex" Tableau bidimensionnel représentant les textures des murs.
 * @param tex_vector Flag indiquant si des textures sont utilisées.
 * @param color Valeur de couleur pour le rendu.
 */
typedef struct s_CameraConfig
{
	double			fov;
	double			camera_x;
	double			plane_x;
	double			plane_y;
	double			raydir_x;
	double			raydir_y;
	double			olddir_x;
	double			oldplane_x;
	int				map_x;
	int				map_y;
	double			ddist_x;
	double			ddist_y;
	double			s_dist_x;
	double			s_dist_y;
	double			perp_wd;
	double			camera_rot;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				wall_dir;
	float			wallhit;
	int				tex_x;
	int				tex_y;
	int				tex_w;
	int				tex_h;
	float			tex_step;
	float			tex_pos;
	int				**tex;
	bool			tex_vector;
	unsigned int	color;
}				t_CameraConfig;

/**
* @struct  t_Menu
* Structure de gestion du menu du jeu dans le projet Cub3D.
*
* La structure 't_Menu' contient des pointeurs vers des textures pour le "start"
* et les boutons "Quit" dans le menu du jeu.
*
* Pointeur @param start vers la configuration de la texture pour le bouton "Démarrer".
* Pointeur @param quit vers la configuration de la texture pour le bouton "Quitter".
*/

typedef struct s_Menu
{
	t_TextureSetup	*start;
	t_TextureSetup	*quit;
}				t_Menu;

/**
 * @struct t_Cub3d
 * Main structure for managing the Cub3D game configuration.
 *
 * The `t_Cub3d` structure is the central configuration structure for the Cub3D
 * game.
 * It holds various components and flags for controlling the game's behavior.
 *
 * @param mlx_ptr Pointer to the MiniLibX connection.
 * @param win_ptr Pointer to the MiniLibX game window.
 * @param img_wall Pointer to an image representing walls.
 * @param img_floor Pointer to an image representing the floor.
 * @param mouse_x Current X-coordinate of the mouse cursor.
 * @param mouse_y Current Y-coordinate of the mouse cursor.
 * @param cam Pointer to the camera configuration structure.
 * @param player Pointer to the player configuration structure.
 * @param map Pointer to the map configuration structure.
 * @param img Pointer to the main game image control structure.
 * @param minimap Pointer to the minimap configuration structure.
 * @param main Pointer to the main menu configuration structure.
 * @param menu_active Flag indicating if the menu is currently active.
 * @param graphics_ok Flag indicating if graphics resources are initialized.
 * @param files_ok Flag indicating if game files are successfully loaded.
 * @param minimap_ok Flag indicating if the minimap is initialized.
 * @param cam_ok Flag indicating if the camera is configured.
 * @param menu_ok Flag indicating if the main menu is initialized.
 * @param gun_ok Flag indicating if the player's gun is set up.
 */

/**
 * @struct t_Cub3d
 * Structure principale de gestion de la configuration du jeu Cub3D.
 *
 * La structure 't_Cub3d' est la structure de configuration centrale pour le Cub3D
 * jeu.
 * Il contient divers composants et indicateurs pour contrôler le comportement du jeu.
 *
 * @param mlx_ptr Pointeur vers la connexion MiniLibX.
 * @param win_ptr Pointeur vers la fenêtre de jeu MiniLibX.
 * @param img_wall Pointeur vers une image représentant des murs.
 * @param img_floor Pointeur vers une image représentant le sol.
 * @param mouse_x Coordonnée X actuelle du curseur de la souris.
 * @param mouse_y Coordonnée Y actuelle du curseur de la souris.
 * @param cam Pointeur  vers la structure de configuration de la caméra.
 * @param player Pointeur vers la structure de configuration du lecteur.
 * @param map Pointeur vers la structure de configuration de la carte.
 * @param img Pointeur vers la structure de contrôle de l'image principale du jeu.
 * @param minimap Pointeur vers la structure de configuration de la minicarte.
 * @param main Pointeur vers la structure de configuration du menu principal.
 * @param menu_active Flag indiquant si le menu est actuellement actif.
 * @param graphics_ok Flag indiquant si les ressources graphiques sont initialisées.
 * @param files_ok Flag indiquant si les fichiers du jeu ont été chargés avec succès.
 * @param minimap_ok Flag indiquant si la minicarte est initialisée.
 * @param cam_ok Flag indiquant si la caméra est configurée.
 * @param menu_ok Flag indiquant si le menu principal est initialisé.
 * @param gun_ok Flag indiquant si l'arme du joueur est configurée.
 */
typedef struct s_Cub3d
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_wall;
	void			*img_floor;
	int				mouse_x;
	int				mouse_y;
	t_CameraConfig	*cam;
	t_PlayerConfig	*player;
	t_MapConfig		*map;
	t_ImageControl	*img;
	t_MiniMap		*minimap;
	t_Menu			*main;
	bool			menu_active;
	bool			graphics_ok;
	bool			files_ok;
	bool			minimap_ok;
	bool			cam_ok;
	bool			menu_ok;
	bool			gun_ok;
}				t_Cub3d;

// FONCTIONS DU CYCLE DE VIE DU PROGRAMME
// Section pour les fonctions de gestion du démarrage, de l'exécution et de la fin du programme.
void	free_main(t_Cub3d *cub);
void	free_textures(t_Cub3d *cub, t_TextureSetup *texture);
void	free_gun(t_Cub3d *cub);
void	free_cam(t_Cub3d *cub);
void	free_menu(t_Cub3d *cub);
int		gameloop(t_Cub3d *cub);

// FONCTIONS D'ANALYSE DE CARTE ET DE FICHIER
// Section pour les fonctions liées à l'analyse des fichiers de carte et à la validation des types de fichiers.
int		map_init(t_Cub3d *cub, char *file);
void	create_temp_map(t_Cub3d *cub, char *line);
int		check_map_validity(t_Cub3d *cub);
int		parse_map_file(t_Cub3d *cub);
int		is_valid_map_type(char *filename);
int		parse_elements(t_Cub3d *cub, int i, char *line);
void	get_map_n_lines(t_Cub3d *cub);
int		has_valid_info(t_Cub3d *cub, char *line);
int		has_valid_info2(t_Cub3d *cub, char *line);
int		has_valid_info3(t_Cub3d *cub, char *line);
int		set_tex_path(t_Cub3d *cub, char *path, int direction);
void	put_floor_ceil_color(t_Cub3d *cub, char *line, int n, int i);
int		fill_matrix(t_Cub3d *cub);
int		check_map_closed(t_Cub3d *cub);
int		check_surroundings(t_MapConfig *m, int i, int j);
int		check_surroundings_utils(t_MapConfig *m, int i, int j, char *charset);
int		get_matrix_borders(t_MapConfig *m, int i, int j);
int		check_walls_doors(t_MapConfig *m, int i, int j);
int		check_north_south(t_Cub3d *cub, char *line);
int		check_west_east(t_Cub3d *cub, char *line);
int		fill_bonus_info(t_Cub3d *cub, char *line);

// FONCTIONS DE GESTION DES JOUEURS
int		set_player_orientation(t_Cub3d *cub, char c);
int		player_gun(t_Cub3d *cub, t_PlayerConfig *p);
void	draw_gun(t_Cub3d *cub, t_PlayerConfig *p, int x, int y);
void	draw_crosshair(t_Cub3d *cub, t_PlayerConfig *p, int x, int y);

// FONCTIONS DE GESTION DE FICHIERS
// Section de gestion des processus de fichiers
void	ft_open(t_Cub3d *cub);
char	*skip_info(t_Cub3d *cub, char *line, int i);

// FONCTIONS GRAPHIQUES DE L'APPLICATION
// Fonctions de gestion des graphiques et des fenêtres
int		graphics(t_Cub3d *cub);
int		check_tex_validity(t_Cub3d *cub);
int		convert_textures(t_Cub3d *cub);
int		check_access(t_Cub3d *cub);
int		is_xpm(t_Cub3d *cub, int id);
void	my_mlx_pixel_put(t_ImageControl *img, int x, int y, int color);
void	load_xpm(t_Cub3d *c, t_ImageControl *i, char *file);

// EVENT HANDLING FUNCTIONS
// Functions related to handling user input events
void	hook_events(t_Cub3d *cub);
int		deal_key(int key, t_Cub3d *cub);
int		on_mouse_move(t_Cub3d *cub);
int		win_close(t_Cub3d *cub);

// PLAYER HANDLING FUNCTIONS
// Functions related to handling player events
int		player_init(t_Cub3d *cub);
void	set_player_position(t_Cub3d *cub);
int		use_action(t_PlayerConfig *p, t_MapConfig *m);
void	shoot_gun(t_Cub3d *cub, t_PlayerConfig *p, int *counter);
int		readmove(t_Cub3d *cub, t_PlayerConfig *p);
void	apply_for_back_move(t_Cub3d *cub, t_PlayerConfig *p, int dir);
void	apply_left_right_move(t_Cub3d *cub, t_PlayerConfig *p, int dir);
void	check_wall_hit(t_Cub3d *cub, double temp_x, double temp_y);

// FONCTIONS DE GESTION DES JOUEURS
// Fonctions liées à la gestion des événements des joueurs
int		camera_init(t_Cub3d *cub);
void	cam_utils_init(t_CameraConfig *cam);

// FONCTIONS DE DIFFUSION DE RAYONS
void	draw_rays(t_Cub3d *cub);
void	ray_per_colum(t_Cub3d *cub, t_CameraConfig *cam, int x);
void	ray_map_pos(t_Cub3d *cub, t_CameraConfig *cam);
void	ray_delt_dist(t_CameraConfig *cam);
void	step_calculation(t_CameraConfig *cam, t_PlayerConfig *p);
void	apply_dda(t_CameraConfig *cam, t_MapConfig *m);
void	calculate_wall_height(t_CameraConfig *cam);
void	get_wall_direction(t_MapConfig *m, t_CameraConfig *c);

// FONCTIONS DE LA MINICARTE
// Fonctions liées au dessin de la minimap
int		draw_minimap(t_Cub3d *cub);
void	init_minimap(t_Cub3d *cub);
void	minimap_new_image(t_Cub3d *cub);
void	draw_static_player(t_Cub3d *cub);
void	draw_static_cube(t_Cub3d *cub, int type);
void	draw_static_map(t_Cub3d *cub);
void	draw_dynamic_player(t_Cub3d *cub);
void	draw_dynamic_cube(t_Cub3d *cub, int type);
void	draw_dynamic_map(t_Cub3d *cub, int temp_x, int temp_y);
int		max_x_array(t_Cub3d *cub);

// FONCTIONS DE TEXTURE ET DE COULEUR
void	render_ceilling_floor(t_Cub3d *cub);
int		*get_texture_addr(t_ImageControl *i);
void	apply_texture(t_Cub3d *cub, t_CameraConfig *c, int x, int id);
int		my_mlx_pixel_get(t_ImageControl *img, int x, int y);

// MENU PRINCIPAL
int		start_menu(t_Cub3d *cub);
void	setup_menu(t_Cub3d *cub, t_TextureSetup *tex, char *file);
int		button_mo(t_Cub3d *cub, t_ImageControl *i, char b);
void	update_button(t_Cub3d *c, t_ImageControl *i, int p, char b);

// UTILS
void	cub3d_new_image(t_Cub3d *cub);
void	restore_doors(t_Cub3d *cub, int x, int y, int i);
int		mouse_hook(int key, int x, int y, t_Cub3d *cub);
void	ft_clean_gnl(int fd, char *line);

#endif
