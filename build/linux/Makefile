CPPLIBS = -lGL -lGLU -lSDL -lSDL_image
INCLUDE_DIR = ../../include
CPPFLAGS = -I${INCLUDE_DIR} ${CPPLIBS}

all:
	mkdir -p bin
	g++ -o bin/badger ../../src/*.cpp ${CPPFLAGS}

actor_tester:
	mkdir -p bin
	g++ -o bin/actor_tester ../../test/config.cpp ../../test/actor_spec.cpp ../../src/actor.cpp ${CPPFLAGS}
