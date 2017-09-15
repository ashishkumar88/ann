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

    /*
    * Training using stochastic gradient descent - mini batch algorithm
    */
    template <size_t rows, size_t cols>
    void train(float (&array)[rows][cols], int epoch, int trainingSize, float learningRate) {
        // iterating through epochs
        for(int i = 0; i < epoch; i++) {
            // single mini batch
            vector<int> indices = getRandomNumbers(0, rows, trainingSize);
            cout << "Processing the " << i << "th epoch. Size of the mini batch : "<< indices.size() << endl;
            y_data.clear();
            for(int j=0; j < indices.size(); j++) {
                // create new vector
                float dataItem[cols];
                int k;
                for(k=0;k<cols-1;k++) 
                    dataItem[k+1] = array[indices[j]][k];
                dataItem[0] = 1.0;
                y_data.push_back(array[indices[j]][k]);
                vector<float> actuals = { array[indices[j]][k] };

                //error for the output layer
                vector<float> outputs  = this->getNetWorkOutput(dataItem) ;
                this->calculateErrorOuterLayer(outputs, actuals);
                int hiddenLayerCount = networkLayers.size() - 2;

                
                auto it = &networkLayers.back();
                for(int i = hiddenLayerCount; i >= 1; i--) {
                    it = it - i;
                    this->calculateInnerLayerError(it);
                }
                break;
            }
            break;
        }
    }

    /*
    * calculate error back propagated from the previous layer
    */
    void calculateInnerLayerError(NetworkLayer* currentLayer) {
        int i=0,j;
        auto nextLayer = currentLayer + 1;
        for(auto it = currentLayer->getNeurons().begin(); it != currentLayer->getNeurons().end(); it++) {
            j = 0;
            float error = 0.0;
            for(auto itj = nextLayer->getNeurons().begin(); itj != nextLayer->getNeurons().end(); itj++) {
                error = error + (currentLayer->getWeights()[j][i]*itj->getError());
                j++;
            }
            error = error*transferDerivative(it->getValue());
            it->setError(error);
            i++;
        }        
    }

    /*
    * calculate error in the output layer
    */
    void calculateErrorOuterLayer(vector<float> outputs, vector<float> actuals) {
        auto it = &networkLayers.back();
        auto list = it->getNeurons().begin();
        float error ;
        for(int p=0;p<outputs.size();p++){        
            cout << actuals[p] << ", " << actuals[p] - outputs[p] << ", " << outputs[p] << ", ";
            error = (actuals[p] - outputs[p])*transferDerivative(outputs[p]);
            cout << error << endl;
            list->setError(error);
            list++;
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

    vector<float> getNetWorkOutput(float dataItem[]) {
        feedForward(dataItem);
        auto back = networkLayers.back();
        vector<Neuron> neurons = back.getNeurons();
        vector<float> outputs;
        for(int i=1; i < neurons.size(); i++) {
            outputs.push_back(neurons[i].getValue());
        }
        return outputs;
    }

    void feedForward(float dataItem[]) {
        auto it = networkLayers.begin();
        it->initializeNeurons(dataItem);
        it++;
        it->forwardPropagate();
        it++;
        it->forwardPropagate();
    }

    float transferDerivative(float output){
        return output*(1.0-output);         
    }

};

#endif
