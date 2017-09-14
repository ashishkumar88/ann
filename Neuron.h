#ifndef NEURON
#define NEURON

class Neuron {
private:
    float value;
public:
    // Neuron(float input) {
    //     value = input;
    // }

    float getValue() {
        return value;
    }

    void setValue(float v) {
        value = v;
    }
};

#endif
