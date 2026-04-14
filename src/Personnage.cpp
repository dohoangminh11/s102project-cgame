#include <SDL_image.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Image.h"
#include "Personnage.h"

// Classe personnage //////////////////////////////////////////////////////////


Personnage::Personnage( Image& image, int x, int y, int direction, int skin_x, int skin_y) :_image(image)
{
    _x=x;
    _y=y;
    _direction=direction;
    _skin_x=skin_x;
    _skin_y=skin_y;

}

void Personnage::dessiner() {
    _image.dessiner(_x,_y,_skin_x*TAILLE_CASE,TAILLE_CASE*(_skin_y+_direction),TAILLE_CASE,TAILLE_CASE);
}

void Personnage::regarderDroite() {
    _direction=2;
}

void Personnage::regarderGauche() {
    _direction=1;
}

void Personnage::regarderHaut() {
    _direction=3;
}

void Personnage::regarderBas() {
    _direction=0;
}

void Personnage::deplacer(int dx, int dy) {
    _x+=dx;
    _y+=dy;
}


bool Personnage::peutBougerVers(int direction, Niveau& niveau)
{
    int caseX = _x / TAILLE_CASE;
    int caseY = _y / TAILLE_CASE;

    switch (direction) {
    case 2: // droite
        caseX++;
        break;
    case 1: // gauche
        caseX--;
        break;
    case 3: // haut
        caseY--;
        break;
    case 0: // bas
        caseY++;
        break;
    }

    return niveau.caseEstLibre(caseX, caseY);
}


int Personnage::getDirection(){
    return _direction;
}

void Personnage::inverserDirection(){
    _direction = 3 - _direction;
}

void mettreAjourAnimation(){
    for (int i=0; i<=3;i++){

    }
}

// Classe Avatar //////////////////////////////////////////////////////////
Avatar::Avatar(Image& image, int x, int y, int direction, int skin_x, int skin_y) :_perso(image, x, y, direction, skin_x, skin_y)
{
}

void Avatar::dessiner() {
    _perso.dessiner();
}

void Avatar::allerDroite(Niveau& niveau) {
    _perso.regarderDroite();
    if (_perso.peutBougerVers(2,niveau)) _perso.deplacer(TAILLE_CASE,0);
}

void Avatar::allerGauche(Niveau& niveau) {
    _perso.regarderGauche();
    if (_perso.peutBougerVers(1,niveau)) _perso.deplacer(-TAILLE_CASE,0);
}

void Avatar::allerHaut(Niveau& niveau) {
    _perso.regarderHaut();
    if (_perso.peutBougerVers(3,niveau)) _perso.deplacer(0,-TAILLE_CASE);
}

void Avatar::allerBas(Niveau& niveau) {
    _perso.regarderBas();
    if (_perso.peutBougerVers(0,niveau)) _perso.deplacer(0,TAILLE_CASE);
}

bool Avatar::touche(Ennemi& ennemi){
    return _perso.getCoo()==ennemi.getCoo();
}


// Classe Ennemi //////////////////////////////////////////////////////////
Ennemi::Ennemi(Image& image, int x, int y, int direction, int skin_x, int skin_y) :_perso(image, x, y, direction, skin_x, skin_y)
{
}

void Ennemi::dessiner() {
    _perso.dessiner();
}

void Ennemi::avancer(Niveau& niveau){
    if (_perso.peutBougerVers(_perso.getDirection(),niveau)){
        switch (_perso.getDirection()) {
            case 2:
                _perso.deplacer(TAILLE_CASE,0);

                break;
            case 1:
                _perso.deplacer(-TAILLE_CASE,0);
                break;
            case 3:
                _perso.deplacer(0,-TAILLE_CASE);
                break;
            case 0:
                _perso.deplacer(0,TAILLE_CASE);
                break;
        }
    }
    else {_perso.inverserDirection();}
}
// class Tuile ////////////////////////////////////////////////////////// Caracteristique d'une tuile en fonction de l'asset assets/objet.png

Tuile::Tuile(){
    _nom="inconnu";
    _x=-1;                                                          //tuile vide pour erreur recherche
    _y=-1;
    _propriete="inconnu";
}

Tuile::Tuile(string nom,int x,int y,string propriete){
    _nom=nom;
    _x=x;
    _y=y;
    _propriete=propriete;
}

void Tuile::afficher(){
    cout << _nom << ": x=" << _x <<", y="  << _y<<", objet "<<_propriete << endl;
}

string Tuile::getnom(){
    return _nom;
}
string Tuile::getprop(){
    return _propriete;
}

int Tuile::getx(){
    return _x;
}

int Tuile::gety(){
    return _y;
}

// class Dictionnaire //////////////////////////////////////////////////////////  cette classe contient une liste de tuile provenant du fichier assets/dictionnaire.txt

Dictionnaire::Dictionnaire(string nomFichier){
    ifstream fichier(nomFichier);

    if (!fichier) {
        cout << "Erreur ouverture fichier" << endl;
        return;
    }

    string ligne;
    getline(fichier, ligne);                                                 //lecture de chaque ligne du fichier sauf de la premiere car elle corespond au nombre de tuile total
    while (getline(fichier, ligne)) {

        string nom;
        int x,y;
        string propriete;

        stringstream ss(ligne);
        ss >> nom >> x >> y >> propriete;
        _Dico.push_back(Tuile(nom,x,y,propriete));
    }
}

void Dictionnaire::afficher(){
    for (int i=0;i<_Dico.size();i++){
        _Dico[i].afficher();
    }
}

Tuile Dictionnaire::recherche(string nom){        //On utilise une recherche dichotomique car on a une liste deja trié
    int debut=0,fin=_Dico.size()-1;
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;

        if (_Dico[milieu].getnom() == nom) {
            return _Dico[milieu];
        }
        else if (nom < _Dico[milieu].getnom()) {
            fin = milieu - 1;
        }
        else {
            debut = milieu + 1;
        }
    }
    return Tuile();
}




// class Objet ////////

Objet::Objet( Image& image,string nom_tuile,Dictionnaire& dico, int x, int y) :_image(image)
{
    _x=x;
    _y=y;
    _tuile=dico.recherche(nom_tuile);
}

void Objet::dessiner(){
    _image.dessiner(_x*TAILLE_CASE,_y*TAILLE_CASE,_tuile.getx()*TAILLE_CASE,_tuile.gety()*TAILLE_CASE,TAILLE_CASE,TAILLE_CASE);
}

Tuile Objet::getTuile(){
    return _tuile;
}

int Objet::getx(){
    return _x;
}

int Objet::gety(){
    return _y;
}

// class Niveau ////////

Niveau::Niveau(Image& image, string nomFichier, Dictionnaire& dico){
    ifstream fichier(nomFichier);

    if (!fichier) {
        cout << "Erreur ouverture fichier" << endl;
        return;
    }

    string ligne;
    getline(fichier, ligne);                                                 //lecture de chaque ligne du fichier sauf de la premiere car elle corespond au nombre de tuile total
    while (getline(fichier, ligne)) {

        string nom;
        int x,y;

        stringstream ss(ligne);

        ss >> nom >> x >> y;
        _niveau.push_back(Objet(image,nom,dico,x,y));
    }
}

void Niveau::dessiner(){
    for(int i=0;i<_niveau.size();i++){
        _niveau[i].dessiner();
    }
}

bool Niveau::caseEstLibre(int x,int y){
    for(int i=0;i<_niveau.size();i++){
        if(_niveau[i].getTuile().getprop()=="solide"){
            if(_niveau[i].getx()==x && _niveau[i].gety()==y){
                return false;
            }
        }
    }
    return true;
}
