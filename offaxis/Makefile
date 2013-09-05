ifeq ($(strip $(OPENCV_HOME)),)
#default OPENCV_HOME
OPENCV_HOME=/usr/local/opencv-2.4.1
endif

CXX=g++
CXXFLAGS=-I../utils -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include
LDFLAGS=-L${OPENCV_HOME}/lib -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_imgproc -lopencv_legacy -lopencv_nonfree -lopencv_calib3d -framework GLUT -framework OpenGL -lobjc

pulsar: glcv.o pulsar.o pulsar_main.o
	${CXX} ${LDFLAGS} glcv.o pulsar.o pulsar_main.o -o pulsar
calibrator: calibrator_main.o calibrator.o
	${CXX} ${LDFLAGS} calibrator_main.o calibrator.o -o calibrator
calibrator_manual: calibrator_manual.o
	${CXX} ${LDFLAGS} calibrator_manual.o -o calibrator_manual

glcv.o: ../utils/glcv.cpp
	${CXX} ${CXXFLAGS} -c $<
.cpp.o:
	${CXX} ${CXXFLAGS} -c $<
.PHONY: clean
clean:
	rm -f *.o pulsar calibrator calibrator_manual
