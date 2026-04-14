#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Moteur.h"

using namespace std;

class Image
{
  Moteur* _moteur;

  // Structures internes de la SDL
  std::shared_ptr<SDL_Texture> _texture;
  int _largeur;
  int _hauteur;

public:

  // Cree un objet image vide
  Image();

  // Charge l'image (PNG par exemple) contenue dans le fichier.
  // Si le fichier n'existe pas, une exception de type `runtime_error` est levee
  Image(Moteur& moteur, const std::string& nomDuFichier);

  // Dessine l'image aux coordonnees voulues
  void dessiner(int x, int y) const;

  // Dessine une partie rectangulaire de l'image aux coordonnees voulues
  void dessiner
    (int x, int y, // coordonnees a l'ecran
     int x_selection, int y_selection, // coordonnees du rectangle dans l'image
     int largeur_selection, // largeur du rectangle dans l'image
     int hauteur_selection  // hauteur du rectangle dans l'image
    ) const;

  // Retourne les dimensions de l'image en pixels
  int getLargeur() const;
  int getHauteur() const;
};

#endif // IMAGE_H
