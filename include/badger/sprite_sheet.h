#ifndef BADGER_SPRITE_SHEET_H
#define BADGER_SPRITE_SHEET_H

#include <SDL_image.h>

namespace Badger {
  class SpriteSheet {
    private:
      unsigned int _texture;
      unsigned int _width;
      unsigned int _height;

      unsigned int _tileWidth;
      unsigned int _tileHeight;

    public:
      SpriteSheet(const char* filename);
      unsigned int texture();

      void textureCoordinates(unsigned int index, double coords[4]);
  };
}

#endif
