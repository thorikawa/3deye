ifeq ($(strip $(OPENCV_HOME)),)
#default OPENCV_HOME
OPENCV_HOME=/usr/local/opencv-2.4.1
endif

ifeq ($(strip $(AR_HOME)),)
AR_HOME=/Users/poly/workspace/ARToolKit
endif

CXX=g++
CXXFLAGS=-arch i386 -I/System/Library/Frameworks/GLUT.framework/Headers -I${OPENCV_HOME}/include -I${AR_HOME}/include
LDFLAGS=-arch i386 -L${AR_HOME}/lib -framework GLUT -framework OpenGL -framework Carbon -framework Cocoa -framework QuickTime -lobjc -lAR -lARgsub -lARvideo

ar: ar.o
	${CXX} ${LDFLAGS} ar.o -o ar
.cpp.o:
	${CXX} ${CXXFLAGS} -c $<
.PHONY: clean
clean:
	rm -f *.o ar
