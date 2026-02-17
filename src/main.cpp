#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Project headers
#include "json.hpp"
#include "preprocess.h"
#include "features.h"
#include "model.h"
#include "tfdif.h"

#include <algorithm>
#include <random>
#include <numeric>

using json = nlohmann::json;

int main()
{
    std::cout << "Day 6: TF-IDF Upgrade Complete \n";

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
        auto tokens = apply_negation (tokenize(clean_text(entry.text)));

        std::vector<std::vector<std::string>> corpus_tokens;

        for (auto &entry : dataset)
        {
            corpus_tokens.push_back(tokenize(clean_text(entry.text)));
        }
        auto idf_values = compute_idf(corpus_tokens, vocab);
        X.clear();
        for (auto &tokens : corpus_tokens)
        {
            X.push_back(compute_tfdif(tokens, vocab, idf_values));
        }
    }

    // Split the dataset into train and test.
    size_t dataset_size = X.size();
    std::vector<size_t> indices(dataset_size);
    std::iota(indices.begin(), indices.end(), 0);

    // Shuffle
    std ::shuffle(indices.begin(), indices.end(),
                  std::default_random_engine(time(0)));

    size_t train_size = dataset_size * 0.8;

    std::vector<std::vector<double>> X_train, X_test;
    std::vector<double> y_train, y_test;

    for (size_t i = 0; i < dataset_size; i++)
    {
        if (i < train_size)
        {
            X_train.push_back(X[indices[i]]);
            y_train.push_back(labels[indices[i]]);
        }
        else
        {
            X_test.push_back(X[indices[i]]);
            y_test.push_back(labels[indices[i]]);
        }
    }

    std::cout << "Training Samples: " << X_train.size() << "\n";
    std::cout << "Testing Samples: " << X_test.size() << "\n";

    // SAFETY CHECK: Ensure features are not all zeros
    bool all_zero = true;
    for (double v : X_train[0])
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

    model.train(X_train, y_train, learning_rate, iterations);

    int TP = 0, TN = 0, FP = 0, FN = 0;

    for (size_t i = 0; i < y_test.size(); i++)
    {
        int pred = model.predict(X_test[i]);

        if (pred == 1 && y_test[i] == 1)
            TP++;
        else if (pred == 1 && y_test[i] == 0)
            FP++;
        else if (pred == 0 && y_test[i] == 0)
            TN++;
        else if (pred == 0 && y_test[i] == 1)
            FN++;
    }

    // Compute metrics
    double accuracy = double(TP + TN) / y_test.size();
    double precision = (TP + FP == 0) ? 0 : double(TP) / (TP + FP);
    double recall = (TP + FN == 0) ? 0 : double(TP) / (TP + FN);

    double f1 = (precision + recall == 0) ? 0 : 2 * precision * recall / (precision + recall);

    // Print results
    std::cout << "Model Evaluation results \n";
    std::cout << "Accuracy: " << accuracy * 100 << "%\n";
    std::cout << "Precision: " << precision * 100 << "%\n";
    std::cout << "Recall: " << recall * 100 << "%\n";
    std::cout << "F1 Score: " << f1 * 100 << "%\n";

    // std::cout << "Labels preview: ";
    // for (int i = 0; i < 10 && i < labels.size(); i++)
    // {
    //     std::cout << labels[i] << " ";
    // }
    // std::cout << "\n";

    // Save Trained Model
    model.save_model("../data/model.json");
    std::cout << "Model saved to data/model.json\n";

    //Save vocab.json
    json vocab_out;
    for (auto &p : vocab)
        vocab_out[p.first] = p.second;

    std::ofstream("../data/vocab.json") << vocab_out.dump(4);

    // Save idf.json
    json idf_out;
    idf_out["idf"] = idf_values;

    std::ofstream("../data/idf.json") << idf_out.dump(4);

    std::string test_sentence;
    std::cout << "\n Enter a sentence to analyze: ";
    std::getline(std::cin, test_sentence);

    std::string cleaned = clean_text(test_sentence);
    std::vector<std::string> tokens = tokenize(cleaned);
    std::vector<double> test_features = vectorize(tokens, vocab);

    double probablity = model.predict_proba(test_features);
    int prediction = model.predict(test_features);

    std::cout << "Test Sentence: " << test_sentence << "\n";
    std::cout << "Prediction Probability: " << probablity << "\n";
    std::cout << "Predicted sentiment: " << (prediction == 1 ? "Positive" : "Negative") << "\n";

    return 0;
}