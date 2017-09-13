#include <iostream>
#include <vector>
#include <fstream>

#include "Network.h"
#include "NetworkLayer.h"
#include "Util.h"


using namespace std;

int main() {
    Network ann;
    NetworkLayer inputLayer(7);
    NetworkLayer hiddenLayer(1);
    NetworkLayer outputLayer(2);

    ann.add(inputLayer, "input").add(hiddenLayer, "hidden").add(outputLayer, "output");
    ann.showLayers();

    //initializing the array of data
    float data[210][8] = {{0.0}};
    Util util ;
    util.loadCSV("./data/seeds_dataset.csv", data);
   
    util.printData(data);
    
    return 0 ;
}
