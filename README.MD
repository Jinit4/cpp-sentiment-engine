# C++ Sentiment Analysis Engine

A C++ project demonstrating core AI, NLP, and data engineering concepts — built from scratch using modern C++ (C++17+), JSON-based data, and modular architecture.

This project mimics how production AI systems work under the hood — focusing on clean data preprocessing, feature extraction, and sentiment analysis logic.

## Day 1 Project Setup & JSON Integration

- Set up the C++ project environment, integrate JSON parsing, and test data reading.
- Initialized a modular CMake project structure:

```bash
cpp-sentiment-engine/
├── src/
├── include/
├── data/
├── external/
├── build/
└── CMakeLists.txt
```

- Installed and used the nlohmann/json library for JSON parsing.
- JSON parsing validated and ready for AI integration.

### Outcome

- Project environment ready for AI development.
- Verified JSON parsing and build pipeline.

## Day 2 Text Preprocessing Module

- Implemented reusable text cleaning and tokenization utilities - foundation for AI-ready text input.
- Implemented preprocess.h and preprocess.cpp with functions:
  - clean_text - removes punctution, lowercase conversion.
  - tokensize() - splits text into tokens.
  - load_dataset() - loads structured data from JSON.
- Updates main.cpp to test preprocessing.
- Printed raw, cleaned and tokenized text for verification.

### Outcome

- Built robust text preprocessing pipeline.
- Modularized preprocessing logic for future ML integration.

## Day 3 Feature Extraction & Sentiment Scoring.

- Added features.h and features.cpp:
- build_vocabulary() -> counts word occurences across dataset.
- compute_sentiment_score() -> calculates sentiment based on word lists.
- Added sentiment_lexicon.json to store positive and negative keywords.

# Outcome

- Introduced AI-driven text scoring in native C++.
- Demonstrated data-driven design via extwernal JSON lexicon.
- Laid foundation for Day 4 ML model integration.

## Day 4 Logistic Regression Model

- Added model.h and model.cpp
- Implemented Logistic Regression classifier from first principles.
- Implemented sigmoid activation and binary cross-entropy loss.
- Implemented batch gradient descent for model training.
- Added model serilization and deserialization using JSON.
- Integrated full training and inference pipeline into main.cpp
- Added extensive debugging checks for feature vectors, labels, and gradients.

# Outcome

- Built a complete ML model without external ML frameworks.
- Demonstrated deep understanding of ML mathematics and optimization.
- Identified and resolved real-world ML failure modes (data symmetry, zero gradients).
- Enabled probabilistic sentiment prediction in native C++.
- Transitioned project from rule-based AI to a trainable ML system.

## Day 5 Train/Test Split & Model Evaluation Metrics

- Implemented proper train/test dataset splitting (80/20) for realistic ML evaluation.
- Added randomized shuffling of samples to prevent ordering bias during training.
- Introduced a complete model evaluation pipeline after training.
- Implemented confusion-matrix based performance tracking:
  - True Positives (TP)
  - True Negatives (TN)
  - False Positives (FP)
  - False Negatives (FN)

- Added industry-standard evaluation metrics:
  - Accuracy
  - Precision
  - Recall
  - F1 Score

- Integrated evaluation directly into main.cpp to validate model generalization.
- Debugged real-world ML challenges such as dataset imbalance and unstable metrics on small datasets.

# Outcome

- Transitioned from simple inference to a complete ML experimentation workflow.
- Enabled proper testing of model performance on unseen data.
- Demonstrated understanding of real ML evaluation beyond accuracy.
- Established a foundation for scalable dataset integration and TF-IDF upgrades in Day 6.
- Brought the project closer to industry-grade ML engineering standards.

# Architecture Overview

```bash
Dataset (JSON)
    ↓
Preprocessing (cleaning, tokenization)
    ↓
Feature Engineering (Bag-of-Words vectorization)
    ↓
Train/Test Split (80/20)
    ↓
Logistic Regression Training (Gradient Descent)
    ↓
Evaluation Metrics (Accuracy, Precision, Recall, F1)
    ↓
Model Saving + Sentiment Prediction

```

# Repo Structure (Current)

```bash
cpp-sentiment-engine/
├── src/
│   ├── main.cpp          # Training + evaluation + inference pipeline
│   ├── preprocess.cpp    # Text cleaning & tokenization
│   ├── features.cpp      # Vocabulary building & vectorization
│   ├── model.cpp         # Logistic Regression implementation
├── include/
│   ├── preprocess.h
│   ├── features.h
│   ├── model.h
├── data/
│   ├── dataset.json      # Training dataset
│   ├── model.json        # Saved trained model
├── external/
│   └── json.hpp          # nlohmann/json (header-only)
├── build/                # CMake build directory Ignored by Git
└── CMakeLists.txt
```
