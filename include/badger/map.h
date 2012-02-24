#ifndef BADGER_MAP_H
#define BADGER_MAP_H

#include "badger/tile.h"

namespace Badger {
	class Map {
		private:
			unsigned int _width;
			unsigned int _height;
			Tile*        _tiles;

		public:
			Map(unsigned int width, unsigned int height);
	};
}

#endif
