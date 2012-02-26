#ifndef BADGER_ACTOR_H
#define BADGER_ACTOR_H

#include <badger/sprite_sheet.h>

namespace Badger {

  class Actor {
    public:
      /*
       * Constructs a Badger::Actor with the appropriate sprites from 
       * the given Badger::SpriteSheet.
       */
      Actor(SpriteSheet* spriteSheet);

      /*
       * Return: the Badger::SpriteSheet for the Actor.
       */
      SpriteSheet* spriteSheet();

    private:

      // The set of sprites for the actor.
      SpriteSheet* _spriteSheet;
  };
}

#endif
