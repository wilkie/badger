#ifndef BADGER_ENGINE_H
#define BADGER_ENGINE_H

#include <badger/renderer.h>
#include <badger/viewport.h>
#include <badger/map.h>

// This is here instead of the cpp because main() is overriden by
// preprocessor magicks.
#ifndef NO_SDL
#include <sdl.h>
#endif

namespace Badger {
  struct VideoSettings {
    unsigned int resolutionX;
    unsigned int resolutionY;
  };

  class Engine {
    public:
      Engine(VideoSettings* video);
      void map(Map* value);

      void run();

    private:
      VideoSettings _video;
      Renderer*     _renderer;
      Viewport*     _mainViewport;
      Map*          _map;

      bool _startSDL();
      bool _initialize();
      void _initViewport();
      void _fireEvent(void* data);

      void _draw();
      void _update();
  };
}

#endif
