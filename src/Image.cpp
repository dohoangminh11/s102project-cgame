#include <SDL_image.h>

#include <exception>

#include "Image.h"

struct Texture_deleter
{
  void operator()(SDL_Texture* t) const
  {
    SDL_DestroyTexture(t);
  }
};

Image::Image()
{

}

Image::Image(Moteur& moteur, const std::string& nomDuFichier)
  : _moteur(&moteur)
{
  SDL_Surface* surface = IMG_Load(nomDuFichier.c_str());
  if (surface == nullptr)
    throw std::runtime_error("Impossible de charger " + nomDuFichier);

  _texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(_moteur->getRenderer(), surface),
                                          Texture_deleter());

  _hauteur = surface->h;
  _largeur = surface->w;
  SDL_FreeSurface(surface);
}

void Image::dessiner(int x, int y) const
{
  SDL_Rect target;
  target.x = x * ECHELLE;
  target.y = y * ECHELLE;
  target.w = _largeur * ECHELLE;
  target.h = _hauteur * ECHELLE;
  SDL_RenderCopy(_moteur->getRenderer(), _texture.get(), nullptr, &target);
}

void Image::dessiner(int x, int y, int rx, int ry, int h, int w) const
{
  SDL_Rect source;
  source.x = rx;
  source.y = ry;
  source.w = w;
  source.h = h;

  SDL_Rect target;
  target.x = x * ECHELLE;
  target.y = y * ECHELLE;
  target.w = source.w * ECHELLE;
  target.h = source.h * ECHELLE;
  SDL_RenderCopy(_moteur->getRenderer(), _texture.get(), &source, &target);
}

int Image::getHauteur() const
{
  return _hauteur;
}

int Image::getLargeur() const
{
  return _largeur;
}
