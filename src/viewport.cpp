#include "badger/viewport.h"

Badger::Viewport::Viewport() {
}

void Badger::Viewport::draw(Renderer* renderer) {
}

Badger::Map* Badger::Viewport::map() {
	return _map;
}

void Badger::Viewport::map(Badger::Map* value) {
	_map = value;
}
