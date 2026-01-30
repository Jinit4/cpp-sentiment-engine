#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

class LogisticRegression
{
private:
    std::vector<double> weights; // Model parameter learned during training
    double bias;                 // Bias term added to the weighted sum
    int feature_size;            // Number of input feaures (size of the vocabulary)

public:
    LogisticRegression(int input_size);
    double sigmoid(double z);
    double predict_proba(const std::vector<double> &x);
    int predict(const std::vector<double> &x);
    void train(const std::vector<std::vector<double>> &X,
               const std::vector<double> &y,
               double learning_rate,
               int iterations); // Trains the model using gradient descent.
    void save_model(const std::string &filename);
    void load_model(const std::string &filename);
};