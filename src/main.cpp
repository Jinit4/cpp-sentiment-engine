#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Project headers
#include "json.hpp"
#include "preprocess.h"
#include "features.h"
#include "model.h"

using json = nlohmann::json;

int main()
{
    std::cout << "Day 4: Logistic Regression Training in C++\n";

    // Load Dataset from JSON
    std::ifstream file("../data/dataset.json");
    if (!file.is_open())
    {
        std::cerr << "Failed to open dataset.json\n";
        return 1;
    }

    json dataset_json;
    file >> dataset_json;

    std::vector<DataEntry> dataset;
    std::vector<double> labels;

    for (const auto &item : dataset_json)
    {
        DataEntry entry;
        entry.text = item["text"];
        dataset.push_back(entry);

        int label_int = item["label"].get<int>();
        labels.push_back(static_cast<double>(label_int));
    }

    std::cout << "Loaded" << dataset.size() << "samples\n";

    // Build Vocabulary from Dataset, Vocab us a map<string, int>, Each unique word becomes a feature

    Vocabulary vocab = build_vocabulary(dataset);
    std::cout << "Vocabulary size: " << vocab.size() << "\n";

    // Convert text into numeric feature vectors

    std::vector<std::vector<double>> X;

    for (const auto &entry : dataset)
    {
        // // clean raw text
        // std::string cleaned = clean_text(entry.text);

        // // Tokenize text
        // std::vector<std::string> tokens = tokenize(cleaned);

        // // Convert tokens into numeric vector
        // std::vector<double> features = vectorize(tokens, vocab);
        auto tokens = tokenize(clean_text(entry.text));
        auto features = vectorize(tokens, vocab);

        X.push_back(features);
    }
    // SAFETY CHECK: Ensure features are not all zeros
    bool all_zero = true;
    for (double v : X[0])
    {
        if (v != 0.0)
        {
            all_zero = false;
            break;
        }
    }

    if (all_zero)
    {
        std::cerr << "❌ ERROR: Feature vector is all zeros. Vocabulary mismatch.\n";
        return 1; // Stop execution before training
    }

    // std::cout << "Debug: First feature vector (first 10 values):\n";
    // for (int i = 0; i < 10 && i < X[0].size(); i++)
    // {
    //     std::cout << X[0][i] << " ";
    // }
    // std::cout << "\n";

    // std::cout << "Convert text to numeric features\n";

    // Create and train Logistic regression model. (No of input features = vocabulary size)

    LogisticRegression model(vocab.size());
    double learning_rate = 0.1;
    int iterations = 1000;

    std::cout << "Training Logistic Regression model ... \n";

    model.train(X, labels, learning_rate, iterations);

    // std::cout << "Labels preview: ";
    // for (int i = 0; i < 10 && i < labels.size(); i++)
    // {
    //     std::cout << labels[i] << " ";
    // }
    // std::cout << "\n";

    // Save Trained Model
    model.save_model("../data/model.json");
    std::cout << "Model saved to data/model.json\n";

    // Test model with a new sentence
    std::string test_sentence = "This product is okay";

    std::string cleaned = clean_text(test_sentence);
    std::vector<std::string> tokens = tokenize(cleaned);
    std::vector<double> test_features = vectorize(tokens, vocab);

    double probablity = model.predict_proba(test_features);
    int prediction = model.predict(test_features);

    std::cout << "Test Sentence: " << test_sentence << "\n";
    std::cout << "Prediction Probability: " << probablity << "\n";
    std::cout << "Predicted sentiment: " << (prediction == 1 ? "Positive" : "Negative") << "\n";

    std::cout << " Day 4 pipeline completed sucessfully\n";
    return 0;
}