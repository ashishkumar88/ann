#include <iostream>
#include <vector>
#include "Network.h"
#include "NetworkLayer.h"

using namespace std;

int main() {
    Network ann;
    NetworkLayer inputLayer(2);
    NetworkLayer hiddenLayer(1);
    NetworkLayer outputLayer(2);

    ann.add(inputLayer, "input").add(hiddenLayer, "hidden").add(outputLayer, "output");
    ann.showLayers();
}
