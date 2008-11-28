rm *.o
g++ -I. -c */*.cpp
g++ -framework GLUT -framework OpenGL -framework Cocoa -framework Foundation -I. *.o  main.cpp
./a.out
 
