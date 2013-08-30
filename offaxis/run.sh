# since OpenCV outputs extra string to stdout, we have to use tail command to get the last two lines
make calibrator pulsar && ./calibrator > calib.tmp && tail -n 2 calib.tmp | ./pulsar
