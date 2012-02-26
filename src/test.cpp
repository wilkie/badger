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
  Badger::Map* map = new Badger::Map(100, 100, sheet);
  Badger::World* world = new Badger::World(map);

  Badger::SpriteSheet* player1SpriteSheet = new Badger::SpriteSheet("assets/blob.png");
  Badger::Actor* player1 = new Badger::Actor(player1SpriteSheet);
  world->addActor(player1);
  engine->world(world);
  engine->run();

  return 0;
}
