#ifndef NETWORKLAYER
#define NETWORKLAYER

#include "Neuron.h"
#include <string>
#include <iostream>

using namespace std ;

class NetworkLayer {
private:
    int size;
    string name;
    vector<Neuron> neurons;
    vector<vector<float>> weights;
public:
    NetworkLayer(int size) {
        this->size = size;
        for(int i=0; i < size; i++) {
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
};

#endif
