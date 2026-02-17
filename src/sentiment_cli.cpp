#include <iostream>
#include <string>

#include "preprocess.h"
#include "features.h"
#include "model.h"

int main()
{
    std::cout << "C++ Sentiment CLI Tool\n";

    // Load trained model
    LogisticRegression model(1);
    model.load_model("../data/model.json");

    // Load vocabulary
    Vocabulary vocab = load_vocabulary("../data/vocab.json");

    std::string input;
    while (true)
    {
        std::cout << "\nEnter a sentence (or type exit): ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        auto tokens = apply_negation(tokenize(clean_text(input)));
        auto vec = compute_tfidf(tokens, vocab, "../data/idf.json");

        double prob = model.predict_proba(vec);
        int pred = model.predict(vec);

        std::cout << "\nPrediction Probability: " << prob << "\n";
        std::cout << "Sentiment: " << (pred ? "Positive " : "Negative ") << "\n";
    }

    return 0;
}