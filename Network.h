#ifndef NETWORK
#define NETWORK

#include "NetworkLayer.h"
#include <iostream>
#include <math.h>
#include <random>

using namespace std ;

class Network {
private:
    vector<NetworkLayer> networkLayers;
    vector<vector<float>> x_data;
    vector<float> y_data;
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

    template <size_t rows, size_t cols>
    void train(float (&array)[rows][cols], int epoch, int trainingSize) {
        // iterating through epochs
        for(int i = 0; i < epoch; i++) {
            // single mini batch
            vector<int> indices = getRandomNumbers(0, rows, trainingSize);
            for(int j=0; j < indices.size(); j++) {
                auto it = networkLayers.begin();
                it->initializeNeurons(array[j]);
            }
        }
    }

    vector<int> getRandomNumbers(int start, int end, int size) {
        default_random_engine generator;
        uniform_int_distribution<int> distribution(start,end);
    
        vector<int> indices;
    
        for (int i=0; i<size; ++i) {
            indices.push_back(distribution(generator));
        }
        return indices;
    }

    float activation(NetworkLayer* layer, int nodeId) {
        float activationValue = -1;
        NetworkLayer current = *layer;
        NetworkLayer previous = *(layer-1);
        int length = previous.getSize();
        vector<vector<float>> weights = previous.getWeights();
        vector<Neuron> neurons = previous.getNeurons();
        for(int i=0; i < length; i++) {
            float nodeValue = neurons[i].getValue();
            activationValue = activationValue + weights[nodeId][i] * nodeValue;
        }
        return activationValue;
    }

    float transfer(float activationValue) {
        float expo = exp(activationValue);
        return 1.0/(1.0 + expo);
    }

    void loadInputData(float data[]) {
        NetworkLayer* firstLayer = &networkLayers.front();
        firstLayer->initializeNeurons(data);
    }
};

#endif
