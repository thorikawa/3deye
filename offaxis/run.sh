# since OpenCV outputs extra string to stdout, we have to use tail command to get the last two lines
make calibrator_manual pulsar && ./calibrator_manual && ./pulsar
