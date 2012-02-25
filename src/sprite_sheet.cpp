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

  _loadStatSheet(filename);

  SDL_FreeSurface(image);
}

void Badger::SpriteSheet::_resizeSpriteArray() {
  Sprite* old = _sprites;

  _sprites = new Sprite[_spriteCount+128];
  memcpy(_sprites, old, sizeof(Sprite) * _spriteCount);
  _spriteCount += 128;

  delete [] old;
}

char* Badger::SpriteSheet::_determineStatSheetFilename(const char* filename) {
  char* stat_sheet = new char[strlen(filename)+2];
  strncpy(stat_sheet, filename, strlen(filename));

  for (unsigned int i = strlen(filename); i > 0; i--) {
    if (stat_sheet[i] == '.') {
      stat_sheet[i] = '\0';
    }
  }

  strcat(stat_sheet, ".txt");

  return stat_sheet;
}

void Badger::SpriteSheet::_loadStatSheet(const char* filename) {
  char* stat_sheet = _determineStatSheetFilename(filename);

  FILE* f = fopen(stat_sheet, "rt");
  
  _spriteCount = 128;
  _sprites = new Sprite[_spriteCount];

  unsigned int spritesLoaded = 0;
  while(!feof(f)) {
    if (_spriteCount == spritesLoaded) {
      _resizeSpriteArray();
    }
    Sprite* sprite = &_sprites[spritesLoaded];
    fscanf(f, "%64s %d, %d, %d, %d\n", sprite->name,
                                    &sprite->x,
                                    &sprite->y,
                                    &sprite->width,
                                    &sprite->height);
    spritesLoaded++;
  }

  _spriteCount = spritesLoaded;

  delete [] stat_sheet;
}

unsigned int Badger::SpriteSheet::texture() {
  return _texture;
}

void Badger::SpriteSheet::textureCoordinates(unsigned int index, double coords[4]) {
  Sprite* sprite = &_sprites[index];

  double tu = (double)sprite->x      / (double)_width;
  double tv = (double)sprite->y      / (double)_height;
  double tw = (double)sprite->width  / (double)_width;
  double th = (double)sprite->height / (double)_height;

  coords[0] = tu;
  coords[1] = tv;
  coords[2] = tw;
  coords[3] = th;
}

bool Badger::SpriteSheet::textureCoordinates(const char* name, double coords[4]) {
  for (unsigned int i = 0; i < _spriteCount; i++) {
    if (strncmp(name, _sprites[i].name, 64) == 0) {
      textureCoordinates(i, coords);
      return true;
    }
  }
  return false;
}
