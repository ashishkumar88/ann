#include <iostream>
#include <vector>
using namespace std;

class Neuron {
private:
    float input;
public:
    Neuron(float input) {
        this->input = input;
    }

    float getInput() {
        return input;
    }
};

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

int main() {
    Network ann;
    NetworkLayer inputLayer(2);
    NetworkLayer hiddenLayer(1);
    NetworkLayer outputLayer(2);

    ann.add(inputLayer, "input").add(hiddenLayer, "hidden").add(outputLayer, "output");
    ann.showLayers();
}