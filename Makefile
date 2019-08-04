CFLAGS = -std=c++17 -Wall -g -Iinclude

LDFLAGS = -lglfw -lGL -ldl -lm -lassimp -lSDL2

EngineTest: src/main.cpp
	g++ $(CFLAGS) -o EngineTest src/main.cpp src/glad.c src/Shader.cpp src/stb_image.cpp src/Mesh.cpp src/Model.cpp src/GameWindow.cpp src/GameApplication.cpp src/GameObject.cpp src/GameObjectList.cpp src/GameScene.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./EngineTest

clean:
	rm -f EngineTest
