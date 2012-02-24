#ifndef BADGER_SPRITE_SHEET_H
#define BADGER_SPRITE_SHEET_H

#include <SDL_image.h>

namespace Badger {
	class SpriteSheet {
		private:
			SDL_Surface* _image;

		public:
			SpriteSheet(const char* filename);
	};
}

#endif
