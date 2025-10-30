#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// Convert tokenized text into word frequency map
std::unordered_map<std::string, int> extract_features(const std::vector<std::string> &tokens);

// Simple sentiment scoring using a lexicon
int compute_sentiment_score(const std::vector<std::string> &tokens);