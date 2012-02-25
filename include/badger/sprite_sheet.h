#ifndef BADGER_SPRITE_SHEET_H
#define BADGER_SPRITE_SHEET_H

#include <SDL_image.h>

namespace Badger {
  /*
   *  Describes an individual sprite on a Badger::SpriteSheet
   */
  struct Sprite {
    /*
     *  The x coordinate of the sprite on the sprite sheet in pixels.
     */
    unsigned int x;

    /*
     *  The y coordinate of the sprite on the sprite sheet in pixels.
     */
    unsigned int y;

    /*
     *  The width of the sprite on the sprite sheet in pixels.
     */
    unsigned int width;

    /*
     *  The height of the sprite on the sprite sheet in pixels.
     */
    unsigned int height;

    /*
     *  The name of the sprite. Maximum 64 characters.
     */
    char name[65];
  };

  /*
   *  Loads an image comprised of many sprites and handles calculations of
   *    texture coordinates.
   */
  class SpriteSheet {
    public:
      /*
       *  Constructs a Badger::SpriteSheet by loading the image located in
       *    the given filename. Will also parse a description file if one
       *    exists by looking for a file with the same name with a 'txt'
       *    extension.
       */
      SpriteSheet(const char* filename);

      /*
       *  Returns: The texture id usable by the Renderer.
       */
      unsigned int texture();

      /*
       *  Fills the given coordinate array with the texture coordinates of the
       *    given sprite. The sprite index is assigned by the order in which
       *    sprites are listed in the description file.
       */
      void textureCoordinates(unsigned int index, double coords[4]);

      /*
       *  Fills the given coordinate array with the texture coordinates of the
       *    given sprite. The sprite is located by comparing the name given
       *    with the one described by the description file.
       *  Returns: true when the sprite is found, false otherwise.
       */
      bool textureCoordinates(const char* name, double coords[4]);

    private:

      // The OpenGL texture index.
      unsigned int _texture;

      // The width and height of the sprite texture.
      unsigned int _width;
      unsigned int _height;

      // The number of sprites contained in the sprite sheet.
      unsigned int _spriteCount;

      // An array of all sprites in the sprite sheet.
      Sprite*      _sprites;

      // Will resize the internal array of sprites (_sprites) when it is full.
      void         _resizeSpriteArray();

      // Yields the filename of the sprite description file from the given
      //   image filename.
      char*        _determineStatSheetFilename(const char* filename);

      // Parse the description file from the given image filename.
      void         _loadStatSheet(const char* filename);
  };
}

#endif
