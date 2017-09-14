#ifndef NETWORK
#define NETWORK

#include "NetworkLayer.h"
#include <iostream>
#include <math.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Util.h"

using namespace std ;

class Network {
private:
    vector<NetworkLayer> networkLayers;
    vector<vector<float>> x_data;
    vector<float> y_data;
public:
    Network& add(NetworkLayer& layer, string name) {
        srand(time(NULL));
        layer.setName(name);
        if(networkLayers.size() != 0) {
            NetworkLayer* last_layer = &networkLayers.back();
            int size_last_layer = last_layer->getSize();
            int size_current_layer = layer.getSize();
            last_layer->initializeWeights(size_current_layer, size_last_layer);
            for(int i=0; i < size_current_layer; i++) {
                for(int j=0; j < size_last_layer+1; j++) {
                    float r = (float) rand()/RAND_MAX;
                    last_layer->setWeight(i,j,r);
                }
            }
        }

        networkLayers.push_back(move(layer));
        return *this;
    }

    void showLayers() {
        for (auto& inner : networkLayers) {
            inner.showNeurons();
        }
    }

    template <size_t rows, size_t cols>
    void train(float (&array)[rows][cols], int epoch, int trainingSize) {
        // iterating through epochs
        for(int i = 0; i < epoch; i++) {
            // single mini batch
            vector<int> indices = getRandomNumbers(0, rows, trainingSize);
            cout << "Processing the " << i << "th epoch. Size of the mini batch : "<< indices.size() << endl;
            y_data.clear();
            for(int j=0; j < indices.size(); j++) {
                auto it = networkLayers.begin();
                // create new vector
                float dataItem[cols];
                int k;
                for(k=0;k<cols-1;k++) 
                    dataItem[k+1] = array[indices[j]][k];
                dataItem[0] = 1.0;
                y_data.push_back(array[indices[j]][k]);
                it->initializeNeurons(dataItem);
                it++;
                it->forwardPropagate();
                it++;
                it->forwardPropagate();
                Util util;

                cout << util.vectorToString(this->getNetWorkOutput()) << endl;
            }
            break;
        }
    }

    vector<int> getRandomNumbers(int start, int end, int size) {
        random_device rd; 
        mt19937 generator(rd()); 
        uniform_int_distribution<int> distribution(start,end);
    
        vector<int> indices;
    
        for (int i=0; i<size; ++i) {
            indices.push_back(distribution(generator));
        }
        return indices;
    }

    void loadInputData(float data[]) {
        NetworkLayer* firstLayer = &networkLayers.front();
        firstLayer->initializeNeurons(data);
    }

    vector<float> getNetWorkOutput() {
        auto it = networkLayers.back();
        vector<Neuron> neurons = it.getNeurons();
        vector<float> outputs;
        for(int i=1; i < neurons.size(); i++) {
            outputs.push_back(neurons[i].getValue());
        }
        return outputs;
    }
};

#endif
