#include <iostream>
#include <vector>
#include <fstream>

#include "Network.h"
#include "NetworkLayer.h"
#include "Util.h"


using namespace std;

int main() {
    Network ann;
    //initializing the array of data
    float data[210][8] = {{0.0}};
    Util util ;
    util.loadCSV("./data/seeds_dataset.csv", data);
    int cols = sizeof data[0] / sizeof(float);

    NetworkLayer inputLayer(cols-1);
    NetworkLayer hiddenLayer(4);
    NetworkLayer outputLayer(1);

    ann.add(inputLayer, "input").add(hiddenLayer, "hidden").add(outputLayer, "output");
    ann.train(data, 100, 150, 0.1);
    //ann.showLayers();
    return 0 ;
}
