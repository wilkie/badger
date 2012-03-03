#include "badger/clock.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

namespace Badger {
  struct ClockPlatformInternal {
#ifdef _WIN32
    LARGE_INTEGER _freq, _start, _end;
#endif
  };
}

Badger::Clock::Clock() {
#ifdef _WIN32
  ClockPlatformInternal* clock = new ClockPlatformInternal;
  _internal = (void*)clock;
  QueryPerformanceFrequency(&clock->_freq);
  QueryPerformanceCounter(&clock->_start);
#endif
}

double Badger::Clock::elapsedTime() {
#ifdef _WIN32
  ClockPlatformInternal* clock = (ClockPlatformInternal*)_internal;
  QueryPerformanceCounter(&clock->_end);
  long amt = (clock->_end.QuadPart - clock->_start.QuadPart) * 1000 / clock->_freq.QuadPart;
  clock->_start = clock->_end;
  return (double)amt / 1000.0;
#endif
}
