SOURCEDIR = src
BUILDDIR = build

CXXFLAGS = -std=c++17 -Wall -g -Iinclude $(shell freetype-config --cflags) -I/usr/include/bullet
LDFLAGS = -lglfw -lGL -ldl -lm -lassimp -lSDL2 -lboost_log_setup -lboost_log -lboost_thread -lboost_system -lpthread -lBulletDynamics -lBulletCollision -lLinearMath $(shell freetype-config --libs)
TARGET = EngineTest
SRCS = $(wildcard $(SOURCEDIR)/*.cpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)\

$(TARGET): $(OBJS) glad
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(OBJS) $(BUILDDIR)/glad.o $(LDFLAGS)
	
glad: $(SOURCEDIR)/glad.c
	$(CXX) -c $(CXXFLAGS) $(SOURCEDIR)/glad.c -o $(BUILDDIR)/glad.o	
	
$(OBJS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) -DBOOST_LOG_DYN_LINK $< -o $@

.PHONY: test clean

test: EngineTest
	echo "No tests. yet ;)"

clean:
	rm -f $(BUILDDIR)/* core *.core $(TARGET)
	
install:
	echo "Installing is not supported"
	
# : $(SOURCEDIR)/glad.c
