# So_long - Mini Jeu 2D

Un jeu 2D simple développé avec la MiniLibX, bibliothèque graphique de l'école 42.

## 📝 Description

So_long est un jeu 2D où le joueur doit collecter tous les items sur une carte et atteindre la sortie. Le projet utilise la MiniLibX pour la gestion des fenêtres, événements et textures.

## 🎮 Fonctionnalités

### Contrôles
- **W** : Haut
- **A** : Gauche
- **S** : Bas
- **D** : Droite
- **ESC** : Quitter

### Éléments de la Carte
| Symbole | Description |
|---------|-------------|
| 1 | Mur |
| 0 | Espace vide |
| P | Position de départ |
| C | Collectible |
| E | Sortie |

## 🛠️ Compilation

```bash
make        # Compile le jeu
make clean  # Nettoie les fichiers objets
make fclean # Nettoie tout
make re     # Recompile
```

## 🎯 Objectifs
- Collecter tous les items
- Atteindre la sortie
- Utiliser le moins de mouvements possible

## ⚙️ Spécifications Techniques
- Gestion de fenêtre fluide
- Affichage 2D (vue de haut)
- Validation de carte (format .ber)
- Gestion des collisions
- Compteur de mouvements

## 🌟 Bonus
- Animations de sprites
- Affichage du score à l'écran
- Ennemis patrouilleurs

---
*Projet réalisé dans le cadre du cursus de l'école 42*
