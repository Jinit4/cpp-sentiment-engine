#pragma once
#include <vector>
#include <map>
#include <string>

using Vocabulary = std ::map<std::string, int>;

std::vector<double> compute_tfdif( // Term Frequency x Inverse Document Frequency
    const std::vector<std::string> &tokens,
    const Vocabulary &vocab,
    const std::vector<double> &idf_values);

std::vector<double> compute_idf(
    const std::vector<std::vector<std::string>> &corpus_tokens,
    const Vocabulary &vocab);