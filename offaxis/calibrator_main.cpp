#include "calibrator.hpp"
#include "common.hpp"

int main (int argc, char *argv[]) {
    CvCapture* capture = cvCreateCameraCapture(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, IN_WIDTH);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, IN_HEIGHT);

    Calibrator* lCalibrator = new Calibrator();
    lCalibrator->start(capture, Calibrator::LEFT);

    Calibrator* rCalibrator = new Calibrator();
    rCalibrator->start(capture, Calibrator::RIGHT);

    cvReleaseCapture(&capture);

    int centerX = (lCalibrator->leftTop.x + rCalibrator->leftTop.x) / 2;
    int centerY = (lCalibrator->leftTop.y + rCalibrator->leftTop.y) / 2;

    fprintf(stderr, "center=(%d, %d)\n", centerX, centerY);

    CvPoint center = cvPoint(centerX, centerY);
    CvPoint lCenter = lCalibrator->convertCoordinates(center);
    CvPoint rCenter = rCalibrator->convertCoordinates(center);

    fprintf(stderr, "left center=(%d, %d)\n", lCenter.x, lCenter.y);
    fprintf(stderr, "right center=(%d, %d)\n", rCenter.x, rCenter.y);

    printf("%d %d\n", lCenter.x, lCenter.y);
    printf("%d %d\n", rCenter.x, rCenter.y);

    return 0;
}
