#include "calibrator.hpp"
#include "pulsar.hpp"

int main (int argc, char *argv[]) {
    Calibrator* leftCalibrator = new Calibrator();
    leftCalibrator->start(Calibrator::LEFT);

    Calibrator* rightCalibrator = new Calibrator();
    rightCalibrator->start(Calibrator::RIGHT);
}