#include "features.h"
#include<unordered_map>
#include <vector>
#include <string>
#include <algorithm>

//Example sentiment lexicon (extend as needed)
std::unordered_map<std::string, int> sentiment_lexicon = {
    {"good",1},
    {"great", 2},
    {"excellent", 3},
    {"bad", -1},
    {"terrible", -2},
    {"horrible", -3},
    {"happy", 2},
    {"sad", -2},
    {"love", 3},
    {"hate", -3},
};

// Convert tokenized text into word frequency map
std::unordered_map<std::string, int> extract_feature(const std::vector<std::string>& tokens) {
    std::unordered_map<std::string, int> features; //Create an unordered_map (a hash table) to store word -> count
    for (const auto& token : tokens){ //Loop through every token in the input vector
        features[token]++;
    }
    return features; 
}

//Compute sentiment score
int compute_sentiment_score(const std::vector<std::string>& tokens){
    //Start sentiment score at 0
    int score = 0;

    //Loop through each token (word)
    for (const auto& token : tokens) {
        //Try to find token in the sentiment_lexicon map
        auto it = sentiment_lexicon.find(token);
        if ( it != sentiment_lexicon.end()){
            score+= it->second; //As first is the text and second is its value we are pointing it to second
        }
    }
    return score;
}