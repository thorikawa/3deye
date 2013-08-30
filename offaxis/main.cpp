#include "calibrator.hpp"
#include "pulsar.hpp"

int main (int argc, char *argv[]) {
    Calibrator* lCalibrator = new Calibrator();
    lCalibrator->start(Calibrator::LEFT);

    Calibrator* rCalibrator = new Calibrator();
    rCalibrator->start(Calibrator::RIGHT);

    int centerX = (lCalibrator->leftTop.x + rCalibrator->leftTop.x) / 2;
    int centerY = (lCalibrator->leftTop.y + rCalibrator->leftTop.y) / 2;

    printf("center=(%d, %d)\n", centerX, centerY);

    CvPoint center = cvPoint(centerX, centerY);
    CvPoint lCenter = lCalibrator->convertCoordinates(center);
    CvPoint rCenter = rCalibrator->convertCoordinates(center);

    printf("left center=(%d, %d)\n", lCenter.x, lCenter.y);
    printf("right center=(%d, %d)\n", rCenter.x, rCenter.y);

    return 0;
}