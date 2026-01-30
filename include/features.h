#pragma once
#include <string>
#include <vector>
#include <map>
#include "preprocess.h"

// Define Vocabulary type (word -> frequency)
using Vocabulary = std::map<std::string, int>;

// Function to build vocabulary from dataset
Vocabulary build_vocabulary(const std::vector<DataEntry> &dataset);

// Function to compute sentiment score for a given sentence
double compute_sentiment_score(
    const std::vector<std::string> &tokens,
    const std::vector<std::string> &positive_words,
    const std::vector<std::string> &negative_words);

std::vector<double> vectorize(              // This function returns a numeric vector
    const std::vector<std::string> &tokens, // Inputs a tokenized sentence
    const Vocabulary &vocab                 // Line 8, Used to define Feature positions and order
);