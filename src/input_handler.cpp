#include "badger/input_handler.h"

Badger::InputHandler::InputHandler() {
}

Badger::InputHandler::~InputHandler() {
  for (unsigned int i = 0; i < _bindings.size(); i++) {
    delete _bindings[i];
  }
}

void Badger::InputHandler::registerEvent(const char* name,
                                         int value,
                                         Badger::KeyBinding primary,
                                         Badger::KeyBinding secondary) {
  Binding* binding = new Binding();

  binding->name      = name;
  binding->value     = value;
  binding->primary   = primary;
  binding->secondary = secondary;

  _bindings.push_back(binding);
}

void Badger::InputHandler::rebindPrimary(const char* name,
                                         KeyBinding primary) {
  for (unsigned int i = 0; i < _bindings.size(); i++) {
    if (strncmp(_bindings[i]->name, name, 128) == 0) {
      _bindings[i]->primary = primary;
      return;
    }
  }
}

void Badger::InputHandler::rebindSecondary(const char* name,
                                           KeyBinding secondary) {
  for (unsigned int i = 0; i < _bindings.size(); i++) {
    if (strncmp(_bindings[i]->name, name, 128) == 0) {
      _bindings[i]->secondary = secondary;
      return;
    }
  }
}

int Badger::InputHandler::yieldEvent(KeyBinding* binding) {
  for (unsigned int i = 0; i < _bindings.size(); i++) {
    if (_bindings[i]->primary.key     == binding->key     &&
        _bindings[i]->primary.shift   == binding->shift   &&
        _bindings[i]->primary.control == binding->control &&
        _bindings[i]->primary.alt     == binding->alt) {
      return _bindings[i]->value;
    }

    if (_bindings[i]->secondary.key     == binding->key     &&
        _bindings[i]->secondary.shift   == binding->shift   &&
        _bindings[i]->secondary.control == binding->control &&
        _bindings[i]->secondary.alt     == binding->alt) {
      return _bindings[i]->value;
    }
  }
  return 0;
}
