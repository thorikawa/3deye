g++ -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -framework GLUT -framework OpenGL -lobjc 2plain.cpp -o 2plain && ./2plain 0.1