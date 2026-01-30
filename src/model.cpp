#include "model.h"
#include <cmath>
#include <iostream>

// Initializing the model
LogisticRegression::LogisticRegression(int input_size)
{
    feature_size = input_size;
    weights = std::vector<double>(feature_size, 0.0);
    bias = 0.0;
}

// Sigmoid Function (Convert any number into a value between 0 and 1)
double LogisticRegression::sigmoid(double z)
{
    return 1.0 / (1.0 + std::exp(-z)); // z = w1x1 + w2x2 + ... + wnxn + bias
}

// Probablity prediction
double LogisticRegression::predict_proba(const std::vector<double> &x)
{
    double z = bias; // start with bias
    for (size_t i = 0; i < x.size(); i++)
    {
        z += weights[i] * x[i]; // Multiply word count x[i] x Weights (importance)
    }
    return sigmoid(z); // Pass through sigmoid or return value between 0 and 1
}

// Class Prediction (0 or 1/ Positive or negative)
int LogisticRegression::predict(const std::vector<double> &x)
{
    return predict_proba(x) >= 0.5 ? 1 : 0;
}

// Training with Gradient Descent.
void LogisticRegression::train(const std::vector<std::vector<double>> &X,
                               const std::vector<double> &y,
                               double learning_rate,
                               int iterations)
{
    size_t n_samples = X.size();
    for (int iter = 0; iter < iterations; iter++)
    {
        // 1. Initialize gradients for this iteration
        std::vector<double> dw(weights.size(), 0.0);
        double db = 0.0;

        // 2. Compute gradients over all samples
        for (size_t i = 0; i < n_samples; i++)
        {
            double p = predict_proba(X[i]); // Reusing your existing predict_proba
            double error = p - y[i];

            for (size_t j = 0; j < weights.size(); j++)
            {
                dw[j] += error * X[i][j]; // Accumulate weight gradients
            }
            db += error; // Accumulate bias gradient
        }

        // 3. Update weights and bias using their RESPECTIVE gradients
        for (size_t j = 0; j < weights.size(); j++)
        {
            // FIX: Use dw[j] here, not db!
            weights[j] -= learning_rate * (dw[j] / n_samples);
        }
        bias -= learning_rate * (db / n_samples);

        // Debugging & Loss printing...
        if (iter % 100 == 0)
        {
            // ... (Your existing loss calculation code)
        }
    }
}

// Save model as JSON
void LogisticRegression::save_model(const std::string &filename)
{
    json model_json;
    model_json["weights"] = weights;
    model_json["bias"] = bias;
    std::ofstream file(filename);
    file << model_json.dump(4);
}

// Load model as JSON
void LogisticRegression::load_model(const std::string &filename)
{
    std::ifstream file(filename);
    json model_json;
    file >> model_json;
    weights = model_json["weights"].get<std::vector<double>>();
    bias = model_json["bias"];
}
