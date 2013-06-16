g++ -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -framework GLUT -framework OpenGL -lobjc teapot.cpp -o teapot
./teapot