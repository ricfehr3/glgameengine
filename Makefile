SOURCEDIR = src
BUILDDIR = build

CXXFLAGS = -std=c++17 -Wall -g -Iinclude $(shell freetype-config --cflags)
LDFLAGS = -lglfw -lGL -ldl -lm -lassimp -lSDL2 -lpthread $(shell freetype-config --libs)
TARGET = EngineTest
SRCS = $(wildcard $(SOURCEDIR)/*.cpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)\

$(TARGET): $(OBJS) glad
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(OBJS) $(BUILDDIR)/glad.o $(LDFLAGS)
	
glad: $(SOURCEDIR)/glad.c
	$(CXX) -c $(CXXFLAGS) $(SOURCEDIR)/glad.c -o $(BUILDDIR)/glad.o	
	
$(OBJS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: test clean

test: EngineTest
	echo "No tests. yet ;)"

clean:
	rm -f $(BUILDDIR)/* core *.core $(TARGET)
	
install:
	echo "Installing is not supported"
	
# : $(SOURCEDIR)/glad.c
