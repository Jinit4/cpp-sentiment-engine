#include <iostream>
#include "json.hpp"
#include "preprocess.h"

using json = nlohmann::json;

int main()
{
    std::cout << "Starting Sentiment Engine: Phase 2 - Data Preprocessing \n";

    // Load Dataset
    auto data = load_dataset("../data/dataset.json");

    // Clean and tokenize one example
    if (!data.empty())
    {
        std::string raw = data[0].text;
        std::string cleaned = clean_text(raw);
        auto tokens = tokenize(cleaned);

        std::cout << "\nRaw text: " << raw << "\n";
        std::cout << "Cleaned text: " << cleaned << "\n";
        std::cout << "\nTokens:\n";
        for (const auto &t : tokens)
            std::cout << "- " << t << "\n ";
    }

    return 0;
}