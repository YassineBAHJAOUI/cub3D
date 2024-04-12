# Cub3D

Cub3D est un projet de l'école 42 inspiré du jeu Wolfenstein 3D. L'objectif est de créer un moteur de rendu graphique 3D utilisant la technique du ray-casting pour afficher une vue dynamique au sein d'un labyrinthe.

## Fonctionnalités

- Affichage de textures différentes sur les murs selon leur orientation (nord, sud, est, ouest)
- Couleurs distinctes pour le sol et le plafond
- Gestion des événements clavier pour les déplacements (touches W, A, S, D) et la rotation de la caméra (flèches gauche et droite)
- Fermeture de la fenêtre avec la touche ESC ou en cliquant sur la croix rouge
- Parsing d'un fichier de description de scène au format .cub
- Gestion des erreurs de configuration dans le fichier .cub
- Utilisation de la minilibX pour la partie graphique

## Compilation

Un Makefile est fourni pour compiler le projet. Les règles disponibles sont :
- `make` ou `make all` : compile le projet
- `make clean` : supprime les fichiers objets
- `make fclean` : supprime les fichiers objets et l'exécutable
- `make re` : recompile entièrement le projet
- `make bonus` : compile le projet avec les fonctionnalités bonus

## Utilisation

./cub3D map.cub

Le programme prend en argument un fichier de description de scène au format .cub.

## Bonus

Des fonctionnalités bonus ont été implémentées :
- Collisions avec les murs
- Minimap
- Portes pouvant être ouvertes et fermées
- Sprites animés
- Rotation de la caméra avec la souris
