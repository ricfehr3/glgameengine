CFLAGS = -std=c++17 -Wall -g -Iinclude $(shell freetype-config --cflags)


##LDFLAGS = -L. -lglfw -lGL -ldl -lm -lassimp -lSDL2 -lpthread -lSDL_console
LDFLAGS = -lglfw -lGL -ldl -lm -lassimp -lSDL2 -lpthread $(shell freetype-config --libs)

#conscflags=-Wall -g -ggdb --std=c99 $(shell freetype-config --cflags)
#consldflags=-lSDL2 -lGL -lm $(shell freetype-config --libs)

all: EngineTest
EngineTest: src/main.cpp
	g++ $(CFLAGS) -o EngineTest src/main.cpp src/glad.c src/Shader.cpp src/stb_image.cpp src/Mesh.cpp src/Model.cpp src/GameWindow.cpp src/GameApplication.cpp src/GameObject.cpp src/GameObjectList.cpp src/GameScene.cpp src/Messenger.cpp src/Console.cpp $(LDFLAGS)

.PHONY: test clean

#consolelib:
#	gcc -fPIC -shared -o libSDL_console.so src/Console/SDL_console.c -Iinclude $(conscflags) $(consldflags)

test: EngineTest
	./run

clean:
	rm -f EngineTest
