#ifndef NETWORKLAYER
#define NETWORKLAYER

#include "Neuron.h"
#include <string>
#include <iostream>   
#include <math.h>   

using namespace std ;

class NetworkLayer {
private:
    int size;
    string name;
    vector<Neuron> neurons;
    vector<vector<float>> weights;
public:
    NetworkLayer(int size) {
        this->size = size+1;
        for(int i=0; i < this->size; i++) {
            Neuron neuron;
            neurons.push_back(neuron);
        }
    }

    int getSize() {
        return size;
    }

    void setName(string s) {
        name = s;
    }

    string getName() {
        return name;
    }

    vector<Neuron> getNeurons() {
        return neurons;
    }

    void setWeight(int row, int column, float value) {
        weights[row][column] = value;
    }

    vector<vector<float>> getWeights() {
        return weights;
    }

    void initializeWeights(int row, int column) {
        for(int i = 0; i < row; i++) {
            vector<float> newRow(column, 0.0);
            weights.push_back(newRow);
        }
    }

    void initializeNeurons(float data[]) {
        int i = 0;
        for(auto it = neurons.begin(); it < neurons.end(); it++) {
            it->setValue(data[i++]);
        }
    }

    void showWeights() {
        for (const auto& inner : weights) {
            for (const auto& item : inner) {
                cout << item << ", ";
            }
            cout << endl;
        }
    }
    
    void showNeurons() {
        for (auto& inner : neurons) {
            cout << inner.getValue() << ", ";
        }
        cout << endl;
    }
    
    float activation(int nodeId) {
        float activationValue = 0;
        NetworkLayer current = *this;
        NetworkLayer previous = *(this-1);
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
        float expo = exp(-activationValue);
        float sig = 1.0/(1.0 + expo);
        return sig;
    }

    void forwardPropagate() {
        for(int i=1; i < size; i++) {
            auto it = neurons.begin();
            it = it + i;
            it->setValue(transfer(activation(i)));
        }
    }
};

#endif
