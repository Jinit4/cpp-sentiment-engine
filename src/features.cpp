#include "features.h"
#include <iostream>
#include <algorithm>

// Function: Build_vocabulary
// Purpose: Count word occurences in the dataset

Vocabulary build_vocabulary(const std::vector<DataEntry> &dataset)
{
    Vocabulary vocab;
    int index = 0;

    for (const auto &entry : dataset)
    {
        // Step 1: Clean the text (remove punctuation, lowecase, etc)
        // std::string cleaned = clean_text(entry.text);
        // // Step 2: Tokenize the cleaned text into individual words
        // auto tokens = tokenize(cleaned);
        auto tokens = tokenize(clean_text(entry.text));

        // Step 3: For each token, increment its frequeny count in th ap
        for (const auto &word : tokens)
            if (vocab.find(word) == vocab.end())
            {
                vocab[word] = index++; // assign unique index
            }
    }

    // print the total number of unique words found in the dataset
    std::cout << "Vocabulary built with " << vocab.size() << "unique words.\n";
    return vocab;
}

// Function: compute_sentiment_score
// Purpose: Compute a simple rule-based sentiment score for a given text.

double compute_sentiment_score(
    const std::vector<std::string> &tokens,         // words from input text
    const std::vector<std::string> &positive_words, // list of positive sentiment words
    const std::vector<std::string> &negative_words  // list of negative sentiment words
)
{
    int pos_count = 0;
    int neg_count = 0;
    // Step 1: Loop through each token(word) in the text
    for (const auto &token : tokens)
    {
        // Check if word is in positive or negative list
        if (std::find(positive_words.begin(), positive_words.end(), token) != positive_words.end())
            pos_count++;
        else if (std::find(negative_words.begin(), negative_words.end(), token) != negative_words.end())
            neg_count++;
    }

    // Compute a simple sentiment score between -1 and +1
    int total = pos_count + neg_count;
    if (total == 0)
        return 0.0;
    return static_cast<double>(pos_count - neg_count) / total;
}
std::vector<double> vectorize(
    const std::vector<std::string> &tokens,
    const Vocabulary &vocab)
{
    std::vector<double> features(vocab.size(), 0.0);

    for (const auto &token : tokens)
    {
        auto it = vocab.find(token);
        if (it != vocab.end())
        {
            features[it->second] += 1.0;
        }
    }

    return features;
}