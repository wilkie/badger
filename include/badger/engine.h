#ifndef BADGER_ENGINE_H
#define BADGET_ENGINE_H

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
			void run();

		private:
			VideoSettings _video;

			bool _startSDL();
			bool _initialize();
			void _initViewport();
			void _fireEvent(void* data);

			void _draw();
			void _update();
	};
}

#endif

