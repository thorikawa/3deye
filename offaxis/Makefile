ifeq ($(strip $(OPENCV_HOME)),)
#default OPENCV_HOME
OPENCV_HOME=/usr/local/opencv-2.4.1
endif

pulsar: glcv.o pulsar.o pulsar_main.o
	g++ -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_nonfree -lopencv_calib3d -framework GLUT -framework OpenGL -lobjc glcv.o pulsar.o pulsar_main.o -o pulsar
calibrator: calibrator_main.o calibrator.o
	g++ -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_nonfree -lopencv_calib3d -lobjc calibrator_main.o calibrator.o -o calibrator
calibrator_manual: calibrator_manual.o
	g++ -I${OPENCV_HOME}/include -L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_nonfree -lopencv_calib3d -lobjc calibrator_manual.o -o calibrator_manual
glcv.o: ../utils/glcv.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include ../utils/glcv.cpp
pulsar_main.o: pulsar_main.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include pulsar_main.cpp
pulsar.o: pulsar.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include pulsar.cpp
calibrator_main.o: calibrator_main.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include calibrator_main.cpp
calibrator.o: calibrator.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include calibrator.cpp
calibrator_manual.o: calibrator_manual.cpp
	g++ -c -I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include calibrator_manual.cpp
clean:
	rm *.o pulsar calibrator calibrator_manual
