#ifndef BADGER_SPRITE_SHEET_H
#define BADGER_SPRITE_SHEET_H

#include <SDL_image.h>

namespace Badger {
  struct Sprite {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;

    char name[65];
  };

  class SpriteSheet {
    private:
      unsigned int _texture;
      unsigned int _width;
      unsigned int _height;

      unsigned int _spriteCount;
      Sprite*      _sprites;

      void         _resizeSpriteArray();
      char*        _determineStatSheetFilename(const char* filename);
      void         _loadStatSheet(const char* filename);

    public:
      SpriteSheet(const char* filename);
      unsigned int texture();

      void textureCoordinates(unsigned int index, double coords[4]);
      void textureCoordinates(const char* name);
  };
}

#endif
