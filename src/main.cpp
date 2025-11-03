#include <iostream>
#include "json.hpp"
#include "preprocess.h"
#include "features.h"
#include<fstream>

using json = nlohmann::json;

int main()
{
    std::cout << "Starting Sentiment Engine: Phase 3 - Feature extraction & scoring\n";

    // Load Dataset
    auto data = load_dataset("../data/dataset.json");

    // Build Vocabilary
    auto vocab = build_vocabulary(data);

    //Load lexicon (positive/negative words)
    std::ifstream f("../data/sentiment_lexicon.json");
    if(!f.is_open()){
        std::cerr << "Could not open sentiment_lexicon.json\n";
        return 1;
    }

    json lexicon;
    f >> lexicon;
    std::vector<std::string> positive = lexicon["positive"];
    std::vector<std::string> negative = lexicon["negative"];

    //Compute sentiment score for first entry
    if(!data.empty()) {
        std::string cleaned =clean_text(data[0].text);
        auto tokens = tokenize(cleaned);
        double score = compute_sentiment_score(tokens, positive, negative);

        std::cout << "\nText: " << data[0].text << "\n";
        std::cout <<"Sentiment score: " << score << "\n";

        if (score >0)
            std::cout << "Positive sentiment\n";
        else if (score < 0)
            std::cout << "Negative sentiment\n";
        else 
            std:: cout << "Neutral sentimenr\n";
    }
    return 0;
}