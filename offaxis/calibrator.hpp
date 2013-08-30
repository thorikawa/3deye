#ifndef _3DEYE_CALIBRATOR_H_
#define _3DEYE_CALIBRATOR_H_

#include <opencv2/opencv.hpp>
#include "common.hpp"

class Calibrator {
private:
    const static int ALLOW_ERROR_COUNT = 5;
    const static int THICKNESS = 2;
    const static int CORNER_ROW = 4;
    const static int CORNER_COLUMN = 5;
    const static int CORNER_COUNT = CORNER_ROW * CORNER_COLUMN;
    int phase;
    int notFindCount;
    bool prevfind;
    CvPoint prevPoint;
    CvScalar color;
    IplImage *chessboard;
    double *storage;
    CvMat homography;
    double wRatio, hRatio;
    int skipCount;
public:
    enum Eye {
        LEFT, RIGHT
    };
    Calibrator();
    void start(Calibrator::Eye eye);
    bool calibrate(IplImage* inputImage, IplImage *destImg);
    CvPoint convertCoordinates(CvPoint p);
};	

#endif