#include <vector>

#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"

using namespace std;

int main(int, char**) // Version special du main, ne pas modifier
{
  // Initialisation du jeu
  Moteur moteur("Mon super jeu vidéo");
  // Initialisation du fond
  Image fond(moteur, "assets/fond.png");

  Image personnage(moteur,"assets/personnages.png");
  Image objet(moteur,"assets/objets.png");
  Ennemi ennemi1(personnage,5*TAILLE_CASE,3*TAILLE_CASE,0,0,4); // initialisation slime
  Ennemi ennemi2(personnage,TAILLE_CASE,5*TAILLE_CASE,1,8,4); // initialisation slime
  Avatar heros(personnage,TAILLE_CASE,2*TAILLE_CASE,0,4,0);
  Dictionnaire dico("assets/dictionnaire.txt");
  Niveau niveau(objet,"assets/niveau.txt",dico);

  // TODO: charger images, creer personnages, etc.

  bool quitter = false;
  // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
  // (en general, 60 fois par seconde)
  while (!quitter)
  {
    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();
    while (evenement != AUCUN)
    {
      switch (evenement)
      {
        // QUITTER = croix de la fenetre ou Echap
        case QUITTER_APPUYE:
          quitter = true;
          break;
        case DROITE_APPUYE:
            heros.allerDroite(niveau);
            break;
        case GAUCHE_APPUYE:
            heros.allerGauche(niveau);
            break;
        case HAUT_APPUYE:
            heros.allerHaut(niveau);
            break;
        case BAS_APPUYE:
            heros.allerBas(niveau);
            break;
        default:
          break;
      }

      evenement = moteur.evenementRecu();
    }

    // II. Mise à jour de l'état du jeu



    // TODO: faire bouger vos personnages, etc.

    // III. Generation de l'image à afficher

    moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment et reinitalise en ecran noir

    // TODO: afficher vos personnages, objets, etc.

    // Permet de centrer l'image.
    fond.dessiner(0,0);
    niveau.dessiner();
    heros.dessiner();
    ennemi1.dessiner();
    ennemi2.dessiner();
    if (moteur.animationsAmettreAjour()){ennemi1.avancer(niveau);ennemi2.avancer(niveau);}
    if (heros.touche(ennemi1) || heros.touche(ennemi2)) {moteur.attendre(2); quitter=true;}
    moteur.finaliserRendu();
    }


  return 0;
}
