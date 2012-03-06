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
  KeyBinding binding2 = {Badger::Key::NONE};

  binding.key = Badger::Key::LEFT;
  binding2.key = Badger::Key::JOY_POV_LEFT;
  _inputHandler->registerEvent("Walk left", 1, &binding, &binding2);
  binding.key = Badger::Key::RIGHT;
  binding2.key = Badger::Key::JOY_POV_RIGHT;
  _inputHandler->registerEvent("Walk right", 2, &binding, &binding2);
  binding.key = Badger::Key::UP;
  binding2.key = Badger::Key::JOY_POV_UP;
  _inputHandler->registerEvent("Walk up", 3, &binding, &binding2);
  binding.key = Badger::Key::DOWN;
  binding2.key = Badger::Key::JOY_POV_DOWN;
  _inputHandler->registerEvent("Walk down", 4, &binding, &binding2);
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

  // Uninitialize the joystick
  //joystick = SDL_JoystickOpen(0);

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
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // Initialize joystick by querying for the first joystick attached.
  SDL_Joystick *joystick;

  SDL_JoystickEventState(SDL_ENABLE);
  joystick = SDL_JoystickOpen(0);

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
static bool _translateSDLKey(Badger::KeyBinding* binding, SDL_Event* event) {
  binding->key = Badger::Key::NONE;
  if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
      case SDLK_LEFT:
        binding->key = Badger::Key::LEFT;
        break;
      case SDLK_RIGHT:
        binding->key = Badger::Key::RIGHT;
        break;
      case SDLK_UP:
        binding->key = Badger::Key::UP;
        break;
      case SDLK_DOWN:
        binding->key = Badger::Key::DOWN;
        break;
      case SDLK_a:
        binding->key = Badger::Key::A;
        break;
      case SDLK_b:
        binding->key = Badger::Key::B;
        break;
      case SDLK_c:
        binding->key = Badger::Key::C;
        break;
      case SDLK_d:
        binding->key = Badger::Key::D;
        break;
      case SDLK_e:
        binding->key = Badger::Key::E;
        break;
      case SDLK_f:
        binding->key = Badger::Key::F;
        break;
      case SDLK_g:
        binding->key = Badger::Key::G;
        break;
      case SDLK_h:
        binding->key = Badger::Key::H;
        break;
      case SDLK_i:
        binding->key = Badger::Key::I;
        break;
      case SDLK_j:
        binding->key = Badger::Key::J;
        break;
      case SDLK_k:
        binding->key = Badger::Key::K;
        break;
      case SDLK_l:
        binding->key = Badger::Key::L;
        break;
      case SDLK_m:
        binding->key = Badger::Key::M;
        break;
      case SDLK_n:
        binding->key = Badger::Key::N;
        break;
      case SDLK_o:
        binding->key = Badger::Key::O;
        break;
      case SDLK_p:
        binding->key = Badger::Key::P;
        break;
      case SDLK_q:
        binding->key = Badger::Key::Q;
        break;
      case SDLK_r:
        binding->key = Badger::Key::R;
        break;
      case SDLK_s:
        binding->key = Badger::Key::S;
        break;
      case SDLK_t:
        binding->key = Badger::Key::T;
        break;
      case SDLK_u:
        binding->key = Badger::Key::U;
        break;
      case SDLK_v:
        binding->key = Badger::Key::V;
        break;
      case SDLK_w:
        binding->key = Badger::Key::W;
        break;
      case SDLK_x:
        binding->key = Badger::Key::X;
        break;
      case SDLK_y:
        binding->key = Badger::Key::Y;
        break;
      case SDLK_z:
        binding->key = Badger::Key::Z;
        break;
      case SDLK_1:
        binding->key = Badger::Key::NUM1;
        break;
      case SDLK_2:
        binding->key = Badger::Key::NUM2;
        break;
      case SDLK_3:
        binding->key = Badger::Key::NUM3;
        break;
      case SDLK_4:
        binding->key = Badger::Key::NUM4;
        break;
      case SDLK_5:
        binding->key = Badger::Key::NUM5;
        break;
      case SDLK_6:
        binding->key = Badger::Key::NUM6;
        break;
      case SDLK_7:
        binding->key = Badger::Key::NUM7;
        break;
      case SDLK_8:
        binding->key = Badger::Key::NUM8;
        break;
      case SDLK_9:
        binding->key = Badger::Key::NUM9;
        break;
      case SDLK_0:
        binding->key = Badger::Key::NUM0;
        break;
      case SDLK_F1:
        binding->key = Badger::Key::F1;
        break;
      case SDLK_F2:
        binding->key = Badger::Key::F2;
        break;
      case SDLK_F3:
        binding->key = Badger::Key::F3;
        break;
      case SDLK_F4:
        binding->key = Badger::Key::F4;
        break;
      case SDLK_F5:
        binding->key = Badger::Key::F5;
        break;
      case SDLK_F6:
        binding->key = Badger::Key::F6;
        break;
      case SDLK_F7:
        binding->key = Badger::Key::F7;
        break;
      case SDLK_F8:
        binding->key = Badger::Key::F8;
        break;
      case SDLK_F9:
        binding->key = Badger::Key::F9;
        break;
      case SDLK_F10:
        binding->key = Badger::Key::F10;
        break;
      case SDLK_F11:
        binding->key = Badger::Key::F11;
        break;
      case SDLK_F12:
        binding->key = Badger::Key::F12;
        break;
    }
  }
  else if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
    binding->key = (Badger::Key::Code)(Badger::Key::MOUSE_0 + event->button.button - 1);
  }
  else if (event->type == SDL_JOYBUTTONDOWN) {
    binding->key = (Badger::Key::Code)(Badger::Key::JOY_0 + event->jbutton.button);
  }
  else if (event->type == SDL_JOYAXISMOTION) {
    if (event->jaxis.axis == 0) {
      // Left-Right
      if (event->jaxis.value < 0) {
        binding->key = Badger::Key::JOY_LEFT;
      }
      else {
        binding->key = Badger::Key::JOY_RIGHT;
      }
    }
    else if (event->jaxis.axis == 1) {
      // Up-Down
      if (event->jaxis.value < 0) {
        binding->key = Badger::Key::JOY_UP;
      }
      else {
        binding->key = Badger::Key::JOY_DOWN;
      }
    }

    // TODO: Further axes ...
    return true;
  }
  else if (event->type == SDL_JOYHATMOTION) {
    // Hats are a bitmask that has a base of:
    int mask = Badger::Key::JOY_POV_UP - 1;

    if (event->jhat.value & SDL_HAT_UP) {
      mask |= 0x1;
    }
    if (event->jhat.value & SDL_HAT_DOWN) {
      mask |= 0x2;
    }
    if (event->jhat.value & SDL_HAT_LEFT) {
      mask |= 0x4;
    }
    if (event->jhat.value & SDL_HAT_RIGHT) {
      mask |= 0x8;
    }

    binding->key = (Badger::Key::Code)mask;
    return (mask && 0xf);
  }

  if (event->type == SDL_KEYDOWN ||
      event->type == SDL_MOUSEBUTTONDOWN ||
      event->type == SDL_JOYBUTTONDOWN) {

    return true;
  }

  return false;
}
#else
#endif

void Badger::Engine::_fireEvent(void* data) {
  SDL_Event* event = (SDL_Event*)data;
  Badger::KeyBinding binding = {Badger::Key::NONE};
  bool pressed = _translateSDLKey(&binding, event);

  int eventType = _inputHandler->yieldEvent(pressed, &binding);

  if (pressed) {
    switch (eventType) {
      case 1:
        _world->actor(0)->animate("walk_left");
        _world->actor(0)->setCurrentState("walk_left");
        break;

      case 2:
        _world->actor(0)->animate("walk_right");
        _world->actor(0)->setCurrentState("walk_right");
        break;

      case 3:
        _world->actor(0)->animate("walk_up");
        _world->actor(0)->setCurrentState("walk_up");
        break;

      case 4:
        _world->actor(0)->animate("walk_down");
        _world->actor(0)->setCurrentState("walk_down");
        break;

      default:
        break;
    }
  }
  else {
    switch (eventType) {
      case 1:
        _world->actor(0)->animate("stand_left");
        _world->actor(0)->setCurrentState("stand");
        break;

      case 2:
        _world->actor(0)->animate("stand_right");
        _world->actor(0)->setCurrentState("stand");
        break;

      case 3:
        _world->actor(0)->animate("stand_up");
        _world->actor(0)->setCurrentState("stand");
        break;

      case 4:
        _world->actor(0)->animate("stand_down");
        _world->actor(0)->setCurrentState("stand");
        break;

      default:
        break;
    }

    if (_inputHandler->isEventHeld(1)) {
      _world->actor(0)->animate("walk_left");
      _world->actor(0)->setCurrentState("walk_left");
    }
    else if (_inputHandler->isEventHeld(2)) {
      _world->actor(0)->animate("walk_right");
      _world->actor(0)->setCurrentState("walk_right");
    }
    else if (_inputHandler->isEventHeld(3)) {
      _world->actor(0)->animate("walk_up");
      _world->actor(0)->setCurrentState("walk_up");
    }
    else if (_inputHandler->isEventHeld(4)) {
      _world->actor(0)->animate("walk_down");
      _world->actor(0)->setCurrentState("walk_down");
    }
  }
}

Badger::InputHandler* Badger::Engine::inputHandler() {
  return _inputHandler;
}
