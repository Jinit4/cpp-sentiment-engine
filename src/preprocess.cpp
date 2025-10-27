#include "preprocess.h"
#include <fstream>
#include <iostream>
#include <cctype>  //for isalpha, isalnum
#include <sstream> //for stringstream

using json = nlohmann::json;

// function1: Load a dataset from a JSOn file.
std::vector<DataEntry> load_dataset(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open dataset file: " << filename << "\n";
        return {}; // Returns an empty vector if file not found
    }

    json dataset;
    file >> dataset; // Parse JSON file into dataset

    std::vector<DataEntry> entries; // create a vector to hold all entries (text+label)
    for (const auto &item : dataset)
    {
        DataEntry e;             // create a new dataentry struct
        e.text = item["text"];   // extract text field from json
        e.label = item["label"]; // extract label
        entries.push_back(e);
    }

    std::cout << "Loaded" << entries.size() << "entries from" << filename << "\n";
    return entries;
}

// Function2 : Clean text
std::string clean_text(const std::string &text)
{
    std::string result;

    for (char c : text)
    { // Loop through each character in the string
        // check if the character is a letter or a space
        if (std::isalpha(static_cast<unsigned char>(c)) || std::isspace(static_cast<unsigned char>(c)))
        {
            result += std::tolower(static_cast<unsigned char>(c));
        }
        // if it is a punctuation, number, emoji skip it.
    }
    return result; // Returns the cleaned string.
}

// Function3: Tokenize
std::vector<std::string> tokenize(const std::string &text)
{
    std::vector<std::string> tokens; // will store individual words
    std::stringstream ss(text);      // Turn the strinf into a stream
    std::string word;                // Temporary variable to hold each extracted word

    // Extract each word seperated by whitespace
    while (ss >> word)
    {
        tokens.push_back(word); // Add the word to the tokens vector
    }
    return tokens;
}