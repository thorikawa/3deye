#include <opencv2/opencv.hpp>
#include "common.hpp"

#define SQUARE_W 100
#define SQUARE_H 100

void initializeImage(IplImage *image) {
    /*
    cvSet(image, cvScalarAll(0), 0);
    cvSetImageROI(image, cvRect(100,100,SQUARE_W,SQUARE_H));
    cvSet(image, cvScalarAll(255), 0);
    cvSetImageROI(image, cvRect(WIDTH-300, 100,SQUARE_W,SQUARE_H));
    cvSet(image, cvScalarAll(255), 0);
    cvSetImageROI(image, cvRect(WIDTH-300, HEIGHT-300,SQUARE_W,SQUARE_H));
    cvSet(image, cvScalarAll(255), 0);
    cvSetImageROI(image, cvRect(100, HEIGHT-300,SQUARE_W,SQUARE_H));
    cvSet(image, cvScalarAll(255), 0);
     */
    cvSetImageROI(image, cvRect(WIDTH/2 - SQUARE_W/2, HEIGHT/2 - SQUARE_H/2,SQUARE_W,SQUARE_H));
    cvSet(image, cvScalarAll(255), 0);
    cvResetImageROI(image);
}

int main () {
    fprintf(stderr, "manual calibration start\n");

    char lWindowName[256] = "lcalib";
    char rWindowName[256] = "rcalib";

    cvNamedWindow(lWindowName, 0);
    cvMoveWindow(lWindowName, LEFT_X_OFFSET, 0);
    IplImage *lImage = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);
    initializeImage(lImage);
    cvShowImage(lWindowName, lImage);

    cvNamedWindow(rWindowName, 0);
    cvMoveWindow(rWindowName, RIGHT_X_OFFSET, 0);
    IplImage *rImage = cvCreateImage(cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);
    initializeImage(rImage);
    cvShowImage(rWindowName, rImage);

    while (1) {
        char c = cvWaitKey(0);
        if (c == '\x1b') {
            break;
        }
    }

    cvReleaseImage(&lImage);
    cvReleaseImage(&rImage);
    cvDestroyWindow(lWindowName);
    cvDestroyWindow(rWindowName);
}
