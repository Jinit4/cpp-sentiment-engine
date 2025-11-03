#pragma once
#include <string>
#include <vector>
#include <map>
#include "preprocess.h"

//Define Vocabulary type (word -> frequency)
using Vocabulary = std::map<std::string, int>;

//Function to build vocabulary from dataset
Vocabulary build_vocabulary(const std::vector<DataEntry>& dataset);

//Function to compute sentiment score for a given sentence
double compute_sentiment_score(
    const std::vector<std::string>& tokens,
    const std::vector<std::string>& positive_words,
    const std::vector<std::string>& negative_words
);