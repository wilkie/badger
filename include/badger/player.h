#ifndef BADGER_PLAYER_H
#define BADGER_PLAYER_H

#include <badger/sprite_sheet.h>

namespace Badger {

  class Player {
    public:
      /*
       * Constructs a Badger::Player with the appropriate sprites from 
       * the given Badger::SpriteSheet.
       */
      Player(SpriteSheet* spriteSheet);

      /*
       * Return: the Badger::SpriteSheet for the Player.
       */
      SpriteSheet* spriteSheet();

    private:

      // The set of sprites for the player.
      SpriteSheet* _spriteSheet;
  };
}

#endif
