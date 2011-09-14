
CPP = g++
RM = rm -f
OBJ  = camera/Camera.o interface/image.o interface/interface.o interface/light.o interface/texture.o objects/Ball.o objects/Cue.o objects/Game.o objects/Point3d.o objects/Point.o objects/Shot.o objects/Table.o physics/physics.o main.o
LINKOBJ  = camera/Camera.o interface/image.o interface/interface.o interface/light.o interface/texture.o objects/Ball.o objects/Cue.o objects/Game.o objects/Point3d.o objects/Point.o objects/Shot.o objects/Table.o physics/physics.o main.o
BIN = cinooka
CXXINCS =
CXXFLAGS = $(CXXINCS) -I.
LIBS = -lGL -lglut -lGLU



all: $(BIN)

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "cinooka" $(LIBS)

camera/Camera.o: camera/Camera.cpp
	$(CPP) -c camera/Camera.cpp -o camera/Camera.o $(CXXFLAGS)

interface/image.o: interface/image.cpp
	$(CPP) -c interface/image.cpp -o interface/image.o $(CXXFLAGS)

interface/interface.o: interface/interface.cpp
	$(CPP) -c interface/interface.cpp -o interface/interface.o $(CXXFLAGS)

interface/light.o: interface/light.cpp
	$(CPP) -c interface/light.cpp -o interface/light.o $(CXXFLAGS)

interface/texture.o: interface/texture.cpp
	$(CPP) -c interface/texture.cpp -o interface/texture.o $(CXXFLAGS)

objects/Ball.o: objects/Ball.cpp
	$(CPP) -c objects/Ball.cpp -o objects/Ball.o $(CXXFLAGS)

objects/Cue.o: objects/Cue.cpp
	$(CPP) -c objects/Cue.cpp -o objects/Cue.o $(CXXFLAGS)

objects/Game.o: objects/Game.cpp
	$(CPP) -c objects/Game.cpp -o objects/Game.o $(CXXFLAGS)

objects/Point3d.o: objects/Point3d.cpp
	$(CPP) -c objects/Point3d.cpp -o objects/Point3d.o $(CXXFLAGS)

objects/Point.o: objects/Point.cpp
	$(CPP) -c objects/Point.cpp -o objects/Point.o $(CXXFLAGS)

objects/Shot.o: objects/Shot.cpp
	$(CPP) -c objects/Shot.cpp -o objects/Shot.o $(CXXFLAGS)

objects/Table.o: objects/Table.cpp
	$(CPP) -c objects/Table.cpp -o objects/Table.o $(CXXFLAGS)

physics/physics.o: physics/physics.cpp
	$(CPP) -c physics/physics.cpp -o physics/physics.o $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)