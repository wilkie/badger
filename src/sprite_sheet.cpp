#include "badger/sprite_sheet.h"

#ifndef NO_GL
  #ifdef _WIN32
  #include <windows.h>
  #endif

  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <math.h>

Badger::SpriteSheet::SpriteSheet(const char* filename) {
  SDL_RWops   *rwop;
  SDL_Surface *image;

  rwop   = SDL_RWFromFile(filename, "rb");
  image = IMG_LoadPNG_RW(rwop);

  if (image == NULL) {
    char* error = IMG_GetError();
    fprintf(stderr, "IMG_LoadPNG_RW: %s\n", error);
  }

  // Create GL texture
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLint  numColors = image->format->BytesPerPixel;
  GLenum textureFormat;
  if (numColors == 4) {
    if (image->format->Rmask == 0x000000ff) {
      textureFormat = GL_RGBA;
    }
    else {
      textureFormat = GL_BGRA_EXT;
    }
  }
  else if (numColors == 3) {
    if (image->format->Rmask == 0x000000ff) {
      textureFormat = GL_RGB;
    }
    else {
      textureFormat = GL_BGR_EXT;
    }
  }

  glTexImage2D(GL_TEXTURE_2D, 0, numColors, image->w, image->h, 0,
               textureFormat, GL_UNSIGNED_BYTE, image->pixels);

  _width  = image->w;
  _height = image->h;

  _tileWidth = 32;
  _tileHeight = 32;
}

unsigned int Badger::SpriteSheet::texture() {
  return _texture;
}

void Badger::SpriteSheet::textureCoordinates(unsigned int index, double coords[4]) {
  unsigned int widthInTiles  = (unsigned int)floor((double)_width  / (double)_tileWidth);
  unsigned int heightInTiles = (unsigned int)floor((double)_height / (double)_tileHeight);

  double x = (double)(index % widthInTiles);
  double y = (double)(index / widthInTiles);

  double tw = (double)_tileWidth  / (double)_width;
  double th = (double)_tileHeight / (double)_height;
  double tu = x * tw;
  double tv = y * th;

  coords[0] = tu;
  coords[1] = tv;
  coords[2] = tw;
  coords[3] = th;
}
