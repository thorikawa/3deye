#include "calibrator.hpp"

#define WINDOW_NAME "calibrator"
#define MONITOR_NAME "monitor"

Calibrator::Calibrator():notFindCount(0),prevfind(false),color(CV_RGB(255,255,255)),phase(0),skipCount(0) {
    chessboard = cvLoadImage("chessboard.jpg");
    storage = (double*)malloc(sizeof(double)*9);
    homography = cvMat(3, 3, CV_64F, storage);
    wRatio = (double)WIDTH / (double)IN_WIDTH;
    hRatio = (double)HEIGHT / (double)IN_HEIGHT;
}

void Calibrator::start(Calibrator::Eye eye) {

    cvNamedWindow(WINDOW_NAME, 0);
    cvNamedWindow(MONITOR_NAME, 0);

    if (eye == Calibrator::LEFT) {
        printf("left eye calibration\n");
        cvMoveWindow(WINDOW_NAME, LEFT_X_OFFSET, 0);
    } else if (eye == Calibrator::RIGHT) {
        printf("right eye calibration\n");
        cvMoveWindow(WINDOW_NAME, RIGHT_X_OFFSET, 0);
    }
    cvMoveWindow(MONITOR_NAME, MONITOR_X_OFFSET, 0);

    CvCapture* capture = cvCreateCameraCapture(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, IN_WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, IN_HEIGHT);
    IplImage *frame = 0;
    IplImage *dst = cvCreateImage( cvSize(WIDTH, HEIGHT), IPL_DEPTH_8U, 3);

	while (1) {
		frame = cvQueryFrame(capture);
        if (!frame) {
            continue;
        }
        if (calibrate(frame, dst)) {
            printf("calibration done\n");
            break;
        }
        cvShowImage(MONITOR_NAME, frame);
        cvShowImage(WINDOW_NAME, dst);

        char c = cvWaitKey(2);
		if (c == '\x1b')
			break;
    }

    cvReleaseImage(&dst);
    cvReleaseCapture(&capture);
    cvDestroyWindow(WINDOW_NAME);
    cvDestroyWindow(MONITOR_NAME);
}

bool Calibrator::calibrate(IplImage* inputImage, IplImage* destImage) {
    //cvFlip(inputImage, NULL, 1);
    // display chess board to destImage and detect it from inputImage simultaneously
    // display chess board
    int cw = chessboard->width;
    int ch = chessboard->height;
    int offx = (WIDTH - cw) / 2;
    int offy = (HEIGHT - ch) / 2;
    int tw   = cw;
    int th   = ch;
    //printf("%d %d %d %d\n", offx, offy, tw, th);
    cvSetImageROI(destImage, cvRect(offx, offy, tw, th));
    cvCopy(chessboard, destImage);
    cvResetImageROI(destImage);

    // start calibration
    int cornerCount;
    //int cornerFlag = CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE | CV_CALIB_CB_FILTER_QUADS;
    int cornerFlag = 0;
    CvSize patternSize = cvSize(CORNER_COLUMN, CORNER_ROW);
    CvPoint2D32f* corners = (CvPoint2D32f*)cvAlloc(sizeof(CvPoint2D32f) * CORNER_COUNT);
    int ret = cvFindChessboardCorners(inputImage, patternSize, corners, &cornerCount);
    printf("chess ret=%d corners=%d\n", ret, cornerCount);
    if (ret) {
        if (++skipCount < 5) {
            return false;
        }
        //cvDrawChessboardCorners(destImage, patternSize, corners, cornerCount, ret);
        // notmalize
        for (int i=0; i<CORNER_COUNT; i++) {
            corners[i].x *= wRatio;
            corners[i].y *= hRatio;
        }
        CvPoint2D32f* srcPoints = (CvPoint2D32f*)cvAlloc(sizeof(CvPoint2D32f) * 4);
        CvPoint2D32f* dstPoints = (CvPoint2D32f*)cvAlloc(sizeof(CvPoint2D32f) * 4);
        srcPoints[0] = cvPoint2D32f(offx+71. , offy+73.);
        srcPoints[1] = cvPoint2D32f(offx+246., offy+73.);
        srcPoints[2] = cvPoint2D32f(offx+71. , offy+205.);
        srcPoints[3] = cvPoint2D32f(offx+246., offy+205.);
        dstPoints[0] = corners[0];
        dstPoints[1] = corners[CORNER_COLUMN-1];
        dstPoints[2] = corners[(CORNER_ROW-1)*CORNER_COLUMN];
        dstPoints[3] = corners[CORNER_COUNT-1];
        leftTop = cvPoint((int)dstPoints[0].x, (int)dstPoints[0].y);
        for (int i=0; i<4; i++) {
            printf("corner[%d] = (%f, %f)\n", i, dstPoints[i].x, dstPoints[i].y);
        }
        
        CvMat srcMat = cvMat(1, 4, CV_32FC2, srcPoints);
        CvMat dstMat = cvMat(1, 4, CV_32FC2, dstPoints);

        if (!cvFindHomography(&dstMat, &srcMat, &homography, CV_RANSAC, 5)) {
            printf("error findHomography\n");
            return false;
        }
        
        
        cvSet (destImage, cvScalarAll(0), 0);
        
        /*
         CvPoint d = this->convertCoordinates(cvPoint((int)(corners[0].x), (int)(corners[0].y)));
         printf("draw1 (%d, %d)\n", d.x, d.y);
         cvCircle(destImage, d, 3, CV_RGB(255,0,0), -1);
         
         CvPoint d2 = this->convertCoordinates(cvPoint((int)(corners[CORNER_COLUMN-1].x), (int)(corners[CORNER_COLUMN-1].y)));
         printf("draw2 (%d, %d)\n", d2.x, d2.y);
         cvCircle(destImage, d2, 3, CV_RGB(0,255,0), -1);
         
         CvPoint d3 = this->convertCoordinates(cvPoint((int)(corners[CORNER_COUNT-1].x), (int)(corners[CORNER_COUNT-1].y)));
         printf("draw2 (%d, %d)\n", d3.x, d3.y);
         cvCircle(destImage, d3, 3, CV_RGB(0,0,255), -1);
         */
        
        CvPoint p1 = this->convertCoordinates(cvPoint(0,0));
        CvPoint p2 = this->convertCoordinates(cvPoint(WIDTH,0));
        CvPoint p3 = this->convertCoordinates(cvPoint(WIDTH,HEIGHT));
        CvPoint p4 = this->convertCoordinates(cvPoint(0,HEIGHT));
        
        cvLine(destImage, p1, p2, CV_RGB(0,255,0));
        cvLine(destImage, p2, p3, CV_RGB(0,255,0));
        cvLine(destImage, p3, p4, CV_RGB(0,255,0));
        cvLine(destImage, p4, p1, CV_RGB(0,255,0));
        return true;
    }
    return false;
}

/**
 * camera -> projector
 * @param p coodinate on camera caputure
 * @return coodinate on virtual projector
 */
CvPoint Calibrator::convertCoordinates (CvPoint p) {
    CvMat *src = cvCreateMat(3, 1, CV_64F);
    CvMat *dst = cvCreateMat(3, 1, CV_64F);
    cvmSet(src, 0, 0, 1.*p.x);
    cvmSet(src, 1, 0, 1.*p.y);
    cvmSet(src, 2, 0, 1.);
    cvMatMul(&homography, src, dst);
    double x = CV_MAT_ELEM(*dst, double, 0, 0);
    double y = CV_MAT_ELEM(*dst, double, 1, 0);
    double z = CV_MAT_ELEM(*dst, double, 2, 0);
    printf("%f %f %f\n", x, y, z);
    return cvPoint((int)(x/z), (int)(y/z));
}
