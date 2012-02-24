#include "badger/sprite_sheet.h"

Badger::SpriteSheet::SpriteSheet(const char* filename) {
	SDL_RWops   *rwop;
	rwop   = SDL_RWFromFile(filename, "rb");
	_image = IMG_LoadPNG_RW(rwop);
	if (_image == NULL) {
		char* error = IMG_GetError();
		fprintf(stderr, "IMG_LoadPNG_RW: %s\n", error);
	}
}
