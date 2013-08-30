#include "pulsar.hpp"
#include "common.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    int lx, ly, rx, ry;
    cin >> lx >> ly >> rx >> ry;
    
    start(argc, argv, LEFT_X_OFFSET + lx, RIGHT_X_OFFSET + rx);

    return 0;
}
