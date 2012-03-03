#include "badger/engine.h"
#include "badger/clock.h"

#include "math.h"

Badger::Engine::Engine(VideoSettings* video) {
  _video = *video;
  if (!_initialize()) {
    return;
  }

  _world = NULL;
  _inputHandler = new InputHandler();

  // Adding some events just because
  KeyBinding binding = {Badger::Key::NONE};

  binding.key = Badger::Key::LEFT;
  _inputHandler->registerEvent("Walk left", 1, &binding, NULL);
  binding.key = Badger::Key::RIGHT;
  _inputHandler->registerEvent("Walk right", 2, &binding, NULL);
  binding.key = Badger::Key::UP;
  _inputHandler->registerEvent("Walk up", 3, &binding, NULL);
  binding.key = Badger::Key::DOWN;
  _inputHandler->registerEvent("Walk down", 4, &binding, NULL);
}

void Badger::Engine::_draw() {
  _renderer->setProjection(_video.resolutionX, _video.resolutionY, 2.0);
  _renderer->clear();
  _mainViewport->draw(_renderer);
}

void Badger::Engine::world(Badger::World* value) {
  _world = value;
  _mainViewport->world(value);
}

void Badger::Engine::run() {
  SDL_Event event;
  Clock* clock = new Clock();
  while(true) {
    if (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        break;
      }
      _fireEvent(&event);
    }

    // Get the time since the last draw/update
    double elapsed = clock->elapsedTime();

    // Update the world
    _world->update(elapsed);
    
    // Draw the world
    _draw();

    // Display
    SDL_GL_SwapBuffers();
  }

  // Destruct SDL
  SDL_Quit();
}

bool Badger::Engine::_initialize() {
  if (_startSDL()) {
    _initViewport();
    return true;
  }

  fprintf(stderr, "Engine cannot initialize.");
  return false;
}

void Badger::Engine::_initViewport() {
  _renderer     = new Renderer();
  _mainViewport = new Viewport();
  _renderer->initializeViewport(_video.resolutionX, _video.resolutionY);
}

bool Badger::Engine::_startSDL() {
#ifdef NO_SDL
  return false;
#else
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

  SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,        1);

  SDL_Surface* surf_display;
  if((surf_display = SDL_SetVideoMode(_video.resolutionX, _video.resolutionY, 32, SDL_HWSURFACE | SDL_OPENGL)) == NULL) {
    fprintf(stderr, "Unable to initialize SDL: SDL_SetVideoMode failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_WM_SetCaption("Badger", "Badger");

  return true;
#endif
}

void Badger::Engine::_fireEvent(void* data) {
  SDL_Event* event = (SDL_Event*)data;
  if (event->type == SDL_KEYDOWN) {
    Badger::KeyBinding binding = {Badger::Key::NONE};
    switch (event->key.keysym.sym) {
      case SDLK_LEFT:
        binding.key = Badger::Key::LEFT;
        break;
      case SDLK_RIGHT:
        binding.key = Badger::Key::RIGHT;
        break;
      case SDLK_UP:
        binding.key = Badger::Key::UP;
        break;
      case SDLK_DOWN:
        binding.key = Badger::Key::DOWN;
        break;
      default:
        break;
    }

    int eventType = _inputHandler->yieldEvent(&binding);

    switch (eventType) {
      case 1:
        _world->actor(0)->animate("walk_left");
        break;

      case 2:
        _world->actor(0)->animate("walk_rght");
        break;

      case 3:
        _world->actor(0)->animate("walk_up");
        break;

      case 4:
        _world->actor(0)->animate("walk_down");
        break;

      default:
        break;
    }
  }
  else if (event->type == SDL_KEYUP) {
    Badger::KeyBinding binding = {Badger::Key::NONE};
    binding.key = Badger::Key::LEFT;
    int eventType = _inputHandler->yieldEvent(&binding);

    switch (eventType) {
      case 1:
        break;

      case 2:
        break;

      case 3:
        break;

      case 4:
        break;

      default:
        break;
    }
  }
}
