#CXXFLAGS=-std=c++17 -O3
CXXFLAGS=-std=c++17 -g

OBJDIR=obj

SOURCES=main.cpp display.cpp ecs/ecscomponent.cpp ecs/ecsentity.cpp ecs/ecscomponentarray.cpp systems/testsystem.cpp systems/objectfactory.cpp components/transformcomponent.cpp components/vertex.cpp components/meshcomponent.cpp systems/loader.cpp systems/rendersystem.cpp systems/shaderprogram.cpp systems/basicshader.cpp mathematics.cpp systems/physicssystem.cpp systems/inputsystem.cpp components/inputcomponent.cpp 

OBJECTS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))
LLIBS=$(shell pkg-config --cflags --libs glew sdl2)

build: $(OBJECTS)
	g++ $(CPPFLAGS) -I $(LLIBS) -o build $(OBJECTS) 

$(OBJECTS): | obj

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cpp %.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp -o $(OBJDIR)/main.o

.PHONY : clean
clean:
	rm build $(OBJECTS)
