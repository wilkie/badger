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

#ifndef NO_SDL
// OMG LONG FUNCTION JEEZ WEEZ CHEEZ WIZ (tm).
static Badger::Key::Code _translateSDLKey(int symbol) {
  switch (symbol) {
    case SDLK_LEFT:
      return Badger::Key::LEFT;
    case SDLK_RIGHT:
      return Badger::Key::RIGHT;
    case SDLK_UP:
      return Badger::Key::UP;
    case SDLK_DOWN:
      return Badger::Key::DOWN;
    case SDLK_a:
      return Badger::Key::A;
    case SDLK_b:
      return Badger::Key::B;
    case SDLK_c:
      return Badger::Key::C;
    case SDLK_d:
      return Badger::Key::D;
    case SDLK_e:
      return Badger::Key::E;
    case SDLK_f:
      return Badger::Key::F;
    case SDLK_g:
      return Badger::Key::G;
    case SDLK_h:
      return Badger::Key::H;
    case SDLK_i:
      return Badger::Key::I;
    case SDLK_j:
      return Badger::Key::J;
    case SDLK_k:
      return Badger::Key::K;
    case SDLK_l:
      return Badger::Key::L;
    case SDLK_m:
      return Badger::Key::M;
    case SDLK_n:
      return Badger::Key::N;
    case SDLK_o:
      return Badger::Key::O;
    case SDLK_p:
      return Badger::Key::P;
    case SDLK_q:
      return Badger::Key::Q;
    case SDLK_r:
      return Badger::Key::R;
    case SDLK_s:
      return Badger::Key::S;
    case SDLK_t:
      return Badger::Key::T;
    case SDLK_u:
      return Badger::Key::U;
    case SDLK_v:
      return Badger::Key::V;
    case SDLK_w:
      return Badger::Key::W;
    case SDLK_x:
      return Badger::Key::X;
    case SDLK_y:
      return Badger::Key::Y;
    case SDLK_z:
      return Badger::Key::Z;
    case SDLK_1:
      return Badger::Key::NUM1;
    case SDLK_2:
      return Badger::Key::NUM2;
    case SDLK_3:
      return Badger::Key::NUM3;
    case SDLK_4:
      return Badger::Key::NUM4;
    case SDLK_5:
      return Badger::Key::NUM5;
    case SDLK_6:
      return Badger::Key::NUM6;
    case SDLK_7:
      return Badger::Key::NUM7;
    case SDLK_8:
      return Badger::Key::NUM8;
    case SDLK_9:
      return Badger::Key::NUM9;
    case SDLK_0:
      return Badger::Key::NUM0;
    case SDLK_F1:
      return Badger::Key::F1;
    case SDLK_F2:
      return Badger::Key::F2;
    case SDLK_F3:
      return Badger::Key::F3;
    case SDLK_F4:
      return Badger::Key::F4;
    case SDLK_F5:
      return Badger::Key::F5;
    case SDLK_F6:
      return Badger::Key::F6;
    case SDLK_F7:
      return Badger::Key::F7;
    case SDLK_F8:
      return Badger::Key::F8;
    case SDLK_F9:
      return Badger::Key::F9;
    case SDLK_F10:
      return Badger::Key::F10;
    case SDLK_F11:
      return Badger::Key::F11;
    case SDLK_F12:
      return Badger::Key::F12;
  }
  return Badger::Key::NONE;
}
#else
#endif

void Badger::Engine::_fireEvent(void* data) {
  SDL_Event* event = (SDL_Event*)data;
  if (event->type == SDL_KEYDOWN) {
    Badger::KeyBinding binding = {Badger::Key::NONE};
    binding.key = _translateSDLKey(event->key.keysym.sym);

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

Badger::InputHandler* Badger::Engine::inputHandler() {
  return _inputHandler;
}
