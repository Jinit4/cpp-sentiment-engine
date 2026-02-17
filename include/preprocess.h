#pragma once
// Prevent multiple inclusion of this header file 

#include <string>
#include <vector>
#include "json.hpp"

//including necessary dependencies.

using json = nlohmann::json;
// Define json alias

//Define Data structures
struct DataEntry {
    std :: string text; //The review or text sentence
    int label; // Sentiment label (1= positive 0 = negative)
};

//Declare functions
std::vector<DataEntry> load_dataset(const std::string& filename);
//Loads dataset from JSON and returns a list of entries

std:: string clean_text(const std::string& text);
//Converts text to lowercase and removes punctuation etc.

std::vector<std::string> tokenize(const std::string& text);
//Splits the cleaned text into individual words.

std::vector<std::string> apply_negation(const std::vector<std::string>& tokens);
//Apply negation and combines words like not to get a better output.
