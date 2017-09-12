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

    void setWeight(int row, int column, float value) {
        weights[row][column] = value;
    }

    void initializeWeights(int row, int column) {
        for(int i = 0; i < row; i++) {
            vector<float> newRow(column, 0.0);
            weights.push_back(newRow);
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
