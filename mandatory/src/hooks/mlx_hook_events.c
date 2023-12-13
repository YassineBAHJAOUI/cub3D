#include "../../headers/cub3d.h"

/**
 * @brief Gère l'événement d'appui sur une touche pour initier le mouvement du joueur.
 *
 * La fonction 'move_press' est appelée lorsqu'un événement d'appui sur une touche est détecté.
 * Il vérifie le code de la clé et définit le drapeau de mouvement du joueur correspondant pour
 * indiquer la direction du mouvement. Cette fonction est principalement utilisée pour initier
 * le mouvement du joueur lorsque des touches telles que HAUT, BAS, GAUCHE ou DROITE sont enfoncées.
 *
 * @param key Le code de la touche enfoncée.
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return Renvoie 0 après avoir défini l'indicateur de mouvement du joueur, ou 1 si un invalide
 * le code clé est fourni.
 */
int	move_press(int key, t_Cub3d *cub)
{
	if (key == UP)
		return (cub->player->up = 1, 0);
	else if (key == DOWN)
		return (cub->player->down = 1, 0);
	else if (key == LEFT)
		return (cub->player->left = 1, 0);
	else if (key == RIGHT)
		return (cub->player->right = 1, 0);
	else if (key == L_ARROW)
		return (cub->player->l_key = 1, 0);
	else if (key == R_ARROW)
		return (cub->player->r_key = 1, 0);
	return (1);
}

/**
 * @brief Gère l'événement de relâchement de touche pour arrêter le mouvement du joueur.
 *
 * La fonction 'move_release' est appelée lorsqu'un événement de relâchement de clé est
 * detected. Il vérifie le code de la clé et efface le drapeau de mouvement du joueur
 * correspondant pour indiquer que le mouvement dans cette direction doit s'arrêter.
 * Cette fonction est principalement utilisée pour arrêter le mouvement du joueur lorsque
 * des touches telles que HAUT, BAS, GAUCHE ou DROITE sont relâchées.
 *
 * @param key Le code de clé de la clé libérée.
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return Renvoie 0 après avoir effacé l'indicateur de mouvement du joueur, ou 1 si un code de clé invalide est fourni.
 */
int	move_release(int key, t_Cub3d *cub)
{
	if (key == UP)
		return (cub->player->up = 0, 0);
	else if (key == DOWN)
		return (cub->player->down = 0, 0);
	else if (key == LEFT)
		return (cub->player->left = 0, 0);
	else if (key == RIGHT)
		return (cub->player->right = 0, 0);
	else if (key == L_ARROW)
		return (cub->player->l_key = 0, 0);
	else if (key == R_ARROW)
		return (cub->player->r_key = 0, 0);
	return (0);
}

/**
 * @brief Gère les événements de pression sur les touches, y compris les actions de jeu et les mouvements des joueurs.
 *
 * La fonction 'on_key_press' est responsable du traitement des événements d'appui sur les touches. Il vérifie le code
 * de la touche et effectue les actions correspondantes telles que la fermeture de la fenêtre lorsque la touche ÉCHAP est enfoncée.
 * De plus, il appelle la fonction 'move_press' pour gérer les mouvements du joueur en fonction des touches enfoncées.
 *
 * @param key Le code de la touche enfoncée.
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return Renvoie 0 après le traitement de l'événement d'appui sur une touche, ou 1 si un code de touche non valide est fourni.
 */
int	on_key_press(int key, t_Cub3d *cub)
{
	if (key == ESC)
		win_close(cub);
	move_press(key, cub);
	if (key == USE)
		use_action(cub->player, cub->map);
	return (0);
}

/**
 * @brief Gère les événements de relâchement des touches, y compris l'arrêt des mouvements du joueur.
 *
 * La fonction 'on_key_release' est responsable du traitement des événements de libération de clé.
 * Il vérifie le code de la touche et effectue les actions correspondantes telles que la fermeture de
 * la fenêtre lorsque la touche ÉCHAP est relâchée. De plus, il appelle la fonction 'move_release'
 * pour arrêter le mouvement du joueur en fonction des touches relâchées.
 *
 * @param key Le code de clé de la clé libérée.
 * @param cub Pointeur vers la structure 't_Cub3d'.
 * @return Renvoie 0 après le traitement de l'événement de libération de clé, ou 1 si un code de clé
 * non valide est fourni.
 */
int	on_key_release(int key, t_Cub3d *cub)
{
	if (key == ESC)
		win_close(cub);
	if (move_release(key, cub))
		return (0);
	return (0);
}

/**
 * @brief Configurer des crochets d'événement pour la fenêtre cub3d.
 *
 * La fonction 'hook_events' enregistre les hooks d'événements pour diverses interactions utilisateur
 * dans la fenêtre Cub3D. Ces crochets incluent la gestion de la fermeture de la fenêtre, des événements
 * d'appui sur les touches, des événements de relâchement des touches et des événements d'appui sur
 * le bouton de la souris. Lorsque ces événements se produisent, les fonctions correspondantes sont
 * appelées pour gérer la réponse de l'application.
 *
 * @param cub Pointeur vers la structure t_Cub3d .
 */
void	hook_events(t_Cub3d *cub)
{
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, win_close, cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, on_key_press, cub);
	mlx_hook(cub->win_ptr, KeyRelease, KeyReleaseMask, on_key_release, cub);
	mlx_hook(cub->win_ptr, ButtonPress, ButtonPressMask, mouse_hook, cub);
}