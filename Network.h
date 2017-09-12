#ifndef NETWORK
#define NETWORK

#include "NetworkLayer.h"
#include <iostream>

using namespace std ;

class Network {
private:
    vector<NetworkLayer> networkLayers;

public:
    Network& add(NetworkLayer& layer, string name) {
        layer.setName(name);
        if(networkLayers.size() != 0) {
            NetworkLayer* last_layer = &networkLayers.back();
            int size_last_layer = last_layer->getSize();
            int size_current_layer = layer.getSize();
            last_layer->initializeWeights(size_current_layer, size_last_layer+1);
            for(int i=0; i < size_current_layer; i++) {
                for(int j=0; j < size_last_layer+1; j++) {
                    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    last_layer->setWeight(i,j,r);
                }
            }
        }
        networkLayers.push_back(move(layer));
        return *this;
    }

    void showLayers() {
        for (auto& inner : networkLayers) {
            inner.showWeights();
        }
    }
};

#endif
