g++ -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_objdetect -framework GLUT -framework OpenGL -lobjc snapshot.cpp && ./a.out 0.5