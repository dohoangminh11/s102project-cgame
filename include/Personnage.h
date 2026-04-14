#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include "Image.h"

using namespace std;

class Niveau;

class Personnage
{
    Image _image;
    int _x;
    int _y;
    int _direction;
    int _skin_x;
    int _skin_y;

public:
    Personnage(Image& image, int x, int y, int direction, int skin_x, int skin_y);

    void dessiner();

    void regarderDroite();

    void regarderGauche();

    void regarderHaut();

    void regarderBas();

    void deplacer(int dx, int dy);

    bool peutBougerVers(int direction,Niveau& niveau);

    int getDirection();

    void inverserDirection();

    vector<int> getCoo() { return vector<int> {_x,_y}; };

    vector<int> getCooskin() { return vector<int> {_skin_x,_skin_y}; };
};

// Classe Ennemi

class Ennemi
{
    Personnage _perso;

public:
    Ennemi(Image& image, int x, int y, int direction, int skin_x, int skin_y);
    void dessiner();
    void hautBas();
    void gaucheDroite();
    void avancer(Niveau& niveau);
    vector<int> getCoo() { return _perso.getCoo(); };

};

// Classe Avatar

class Avatar
{
    Personnage _perso;

public:
    Avatar(Image& image, int x, int y, int direction, int skin_x, int skin_y);
    void dessiner();
    void allerDroite(Niveau& niveau);
    void allerGauche(Niveau& niveau);
    void allerHaut(Niveau& niveau);
    void allerBas(Niveau& niveau);
    bool touche(Ennemi& ennemi);
};

// Classe Tuile

class Tuile
{
    string _nom;
    int _x;
    int _y;
    string _propriete;
public:
    Tuile();
    Tuile(string nom,int x,int y,string propriete);
    void afficher();
    string getnom();
    string getprop();
    int getx();
    int gety();
};

// Classe Dictionnaire

class Dictionnaire
{

    vector<Tuile> _Dico;


public:
    Dictionnaire(string nomFichier);
    void afficher();
    Tuile recherche(string nom);

};

// Classe objet

class Objet
{
    Image _image;
    int _x;
    int _y;     //placement de l'objet sur le niveau
    Tuile _tuile;

public:
    Objet(Image& image, string nom_tuile, Dictionnaire& dico, int x, int y);
    void dessiner();
    Tuile getTuile();
    int getx();
    int gety();

};

// Classe Niveau

class Niveau
{
    vector<Objet> _niveau;

public:
    Niveau(Image& image, string nomFichier, Dictionnaire& dico);
    void dessiner();
    bool caseEstLibre(int x,int y);

};

#endif // PERSONNAGE_H_INCLUDED
