# Makefile for building a simple Allegro game
CXX = g++
CXXFLAGS = -g
LDFLAGS = -lalleg -lX11 -lpthread

BUILD_DIR = build

SOURCES = main.cpp 
# Menu.cpp Config.cpp GameStateManager.cpp Ground.cpp Personagem.cpp Inimigo.cpp Shooting.cpp LevelManager.cpp Escada.cpp GameObject.cpp
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = mygame

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(BUILD_DIR)

.PHONY: all clean