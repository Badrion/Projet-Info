#ifndef BRUSH_H
#define BRUSH_H

#define COLOR_TERMINAL 7

typedef enum{
  COLOR_VOID,
  COLOR_WATER,
  COLOR_SAND, 
  COLOR_GRASS,

  COLOR_NOUVEAU_JEU,
  COLOR_REPRENDRE_JEU,
  COLOR_QUITTER_JEU,

  TERMINAL, // l'id de la couleur du terminal est 7

  COLOR_BOIS,
  COLOR_STONE,

  COLOR_STAT,
  COLOR_INVENTAIRE_NEUTRE,
  COLOR_INVENTAIRE_ACTIF,
  COLOR_DIALOGUE
}Color;

typedef enum{
  BRUSH_VOID,
  BRUSH_WATER,
  BRUSH_SAND,
  BRUSH_GRASS,

  BRUSH_BOIS,
  BRUSH_STONE,

  BRUSH_NOUVEAU_JEU,
  BRUSH_REPRENDRE_JEU,
  BRUSH_QUITTER_JEU
}Brush;

#endif