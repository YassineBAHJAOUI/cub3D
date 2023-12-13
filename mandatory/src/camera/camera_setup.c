#include "../../headers/cub3d.h"

/**
 * @brief Initialise la configuration de la caméra pour le lancer de rayons.
 *
 * Cette fonction définit les différents champs de la structure de configuration
 * de la caméra sur leurs valeurs initiales. Il est généralement appelé avant
 * d'effectuer la diffusion de rayons et la détection de collision pour s'assurer
 * que les variables liées à la caméra commencent par les valeurs appropriées.
 *
 * @param cam Pointeur vers la structure de configuration t_Camera à initialiser.
 */
void	cam_utils_init(t_CameraConfig *cam)
{
	cam->s_dist_x = 0;
	cam->s_dist_y = 0;
	cam->perp_wd = 0;
	cam->step_x = 0;
	cam->step_y = 0;
	cam->hit = 0;
	cam->side = 0;
	cam->line_height = 0;
	cam->draw_start = 0;
	cam->draw_end = 0;
}

/**
 * @brief Initialise la configuration de la caméra.
 *
 * Cette fonction initialise la structure de configuration de la caméra,
 * en définissant le champ de vision (FOV) sur une valeur par défaut
 * et en marquant la caméra comme valide.
 *
 * @param cub Pointeur vers la structure principale du jeu (t_Cub3d).
 * @return Renvoie 0 en cas de succès, ou 1 si l'allocation de mémoire échoue.
 */
int	camera_init(t_Cub3d *cub)
{
	cub->cam = ft_calloc(1, sizeof(t_CameraConfig));
	if (!cub->cam)
		return (1);
	cub->cam->fov = 1;
	cub->cam_ok = true;
	return (0);
}