ifeq ($(strip $(OPENCV_HOME)),)
#default OPENCV_HOME
OPENCV_HOME=/usr/local/opencv-2.4.1
endif

pulsar: glcv.o pulsar.o main.o calibrator.o
	g++ -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_nonfree -lopencv_calib3d -framework GLUT -framework OpenGL -lobjc glcv.o pulsar.o main.o calibrator.o -o pulsar
glcv.o: ../utils/glcv.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include ../utils/glcv.cpp
pulsar.o: pulsar.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include pulsar.cpp
main.o: main.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include main.cpp
calibrator.o: calibrator.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include calibrator.cpp
clean:
	rm *.o pulsar
