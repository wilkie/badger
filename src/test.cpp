#include "badger.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv) {
	// initialize engine
	Badger::VideoSettings settings;
	settings.resolutionX = WIDTH;
	settings.resolutionY = HEIGHT;
	Badger::Engine* engine = new Badger::Engine(&settings);
	Badger::SpriteSheet* sheet = new Badger::SpriteSheet("assets/floortiles.png");
	engine->run();

	return 0;
}
