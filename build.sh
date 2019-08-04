g++ -Wall -g            \
src/main.cpp            \
src/glad.c              \
src/Shader.cpp          \
src/stb_image.cpp       \
src/Mesh.cpp            \
src/Model.cpp           \
src/GameWindow.cpp      \
src/GameApplication.cpp \
src/GameObject.cpp      \
src/GameObjectList.cpp  \
src/GameScene.cpp       \
-o turds -Iinclude -lglfw -lGL -ldl -lm -lassimp -lSDL2
