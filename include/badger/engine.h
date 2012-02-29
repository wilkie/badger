#ifndef BADGER_ENGINE_H
#define BADGER_ENGINE_H

#include <badger/renderer.h>
#include <badger/viewport.h>
#include <badger/input_handler.h>
#include <badger/map.h>

// This is here instead of the cpp because main() is overriden by
// preprocessor magicks.
#ifndef NO_SDL
#include <SDL/SDL.h>
#endif

namespace Badger {
  /*
   *  Describes the display configuration the Engine should attempt to use.
   */
  struct VideoSettings {
    /*
     *  The horizontal resolution.
     */
    unsigned int resolutionX;

    /*
     *  The vertical resolution.
     */
    unsigned int resolutionY;
  };

  /*
   *  Handles rendering and most major logic.
   */
  class Engine {
    public:
      /*
       *  Construct an Engine initialized with the given display configuration
       */
      Engine(VideoSettings* video);

      /*
       *  Attach the given Badger::World.
       */
      void world(World* value);

      /*
       *  Attach the given Badger::InputHandler.
       */
      void inputHandler(InputHandler* value);

      /*
       *  Execute the game loop. There is no escape from this function until the game ends.
       */
      void run();

    private:

      // Internal storage
      VideoSettings _video;
      Renderer*     _renderer;
      Viewport*     _mainViewport;
      World*        _world;
      InputHandler* _inputHandler;

      // Initialization methods
      bool _startSDL();
      bool _initialize();
      void _initViewport();

      // Input event handler
      void _fireEvent(void* data);

      // Called to draw a frame
      void _draw();

      // Called to update all game objects
      void _update();
  };
}

#endif
