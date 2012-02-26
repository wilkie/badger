#ifndef BADGER_ACTOR_H
#define BADGER_ACTOR_H

#include <badger/sprite_sheet.h>
#include <badger/position.h>

namespace Badger {

  class Actor {
    public:
      /*
       * Constructs a Badger::Actor using the actor files in the
       * given filepath. The sprite used is defined by the given
       * Badger::SpriteSheet.
       */
      Actor(const char* actorFile,
            SpriteSheet* spriteSheet,
            unsigned int x,
            unsigned int y);

      /*
       * Return: the Badger::SpriteSheet for the Badger::Actor.
       */
      SpriteSheet* spriteSheet();

      /*
       * Return: the Badger::Position for the Badger::Actor.
       */
      Position position();

    private:

      // The set of sprites for the Actor.
      SpriteSheet* _spriteSheet;

      // The current position of the Actor in the world.
      Position _position;
  };
}

#endif
