

OUT := program
CXX := g++
CXXFLAGS := -o
TARGET := Debug/main
SRC := Engine/*.cpp
INCLUDES := -lGL -lGLEW -lSDLmain -lSDL2 -lSDL2_ttf

linux:
	$(CXX) $(CXXFLAGS) $(TARGET) $(SRC) $(INCLUDES)