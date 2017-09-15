#ifndef NEURON
#define NEURON

class Neuron {
private:
    float value;
    float error;
public:
    Neuron() {
        value = 1.0;
    }
    
    Neuron(float input) {
        value = input;
    }

    float getValue() {
        return value;
    }

    void setValue(float v) {
        value = v;
    }
    
    float getError() {
        return error;
    }

    void setError(float e) {
        error = e;
    }
};

#endif
