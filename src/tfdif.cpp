#include "tfdif.h"
#include <cmath>
#include <algorithm>

// Compute IDF values across corpus
std::vector<double> compute_idf(
    const std::vector<std::vector<std::string>> &corpus_tokens,
    const Vocabulary &vocab)
{
    int N = corpus_tokens.size();
    std::vector<double> idf(vocab.size(), 0.0);

    for (const auto &[word, idx] : vocab)
    {
        int doc_count = 0;

        for (const auto &doc : corpus_tokens)
        {
            if (std::find(doc.begin(), doc.end(), word) != doc.end())
                doc_count++;
        }

        idf[idx] = std::log((double)N / (1 + doc_count));
    }
    return idf;
}

// Compute TF-IDF vector for one sentence
std::vector<double> compute_tfdif(
    const std::vector<std::string> &tokens,
    const Vocabulary &vocab,
    const std::vector<double> &idf_values)
{
    std::vector<double> vec(vocab.size(), 0.0);

    for (const auto &token : tokens)
    {
        if (vocab.count(token))
        {
            int idx = vocab.at(token);
            vec[idx] += 1.0;
        }
    }

    // Multiply TF by IDF
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] *= idf_values[i];
    }

    return vec;
}