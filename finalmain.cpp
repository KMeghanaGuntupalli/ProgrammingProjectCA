// main.cpp

#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <iomanip> // For std::hex
#include "TwoLevelBranchPredictor.hpp"
#include "HybridBranchPredictor.hpp"
#include "AccuracyCalculator.hpp"

void simulateWorkload(const std::vector<std::pair<int, std::pair<bool, bool> > >& userInputs, TwoLevelBranchPredictor& twoLevelPredictor, HybridBranchPredictor& hybridPredictor, AccuracyCalculator& accuracyCalculator) {
    for (const auto& input : userInputs) {
        int address = input.first;
        bool actualOutcome = input.second.first;
        bool expectedOutcome = input.second.second;

        bool twoLevelPrediction = twoLevelPredictor.predict();
        bool hybridPrediction = hybridPredictor.predict();

        // Print values of Two-Level and Hybrid predictors
        std::cout << "Address: " << std::hex << std::setw(8) << std::setfill('0') << address
                  << ", Actual Outcome: " << actualOutcome
                  << ", Two-Level Predictor: " << twoLevelPrediction
                  << ", Hybrid Predictor: " << hybridPrediction << std::endl;

        // Update accuracy calculator
        accuracyCalculator.updateAccuracy(expectedOutcome, twoLevelPrediction, hybridPrediction);

        // Update predictors
        twoLevelPredictor.update(expectedOutcome);
        hybridPredictor.update(expectedOutcome);
    }

    // Output accuracies
    accuracyCalculator.printAccuracies();
}

int main() {
    int numInputs;

    // Get the number of inputs from the user
    std::cout << "Enter the number of inputs you want to provide: ";
    std::cin >> numInputs;

    std::vector<std::pair<int, std::pair<bool, bool> > > userInputs;

    // User input
    for (int i = 0; i < numInputs; i++) {
        int address;
        bool actualOutcome, expectedOutcome;

        std::cout << "Enter 8-digit hexadecimal address, actual outcome (0 or 1), and expected outcome (0 or 1) separated by space:" << std::endl;
        std::cin >> std::hex >> address >> actualOutcome >> expectedOutcome;

        userInputs.push_back(std::make_pair(address, std::make_pair(actualOutcome, expectedOutcome)));
    }

    TwoLevelBranchPredictor twoLevelPredictor(8, 512);
    HybridBranchPredictor hybridPredictor(8, 512, 8, 512, 16);
    AccuracyCalculator accuracyCalculator;

    simulateWorkload(userInputs, twoLevelPredictor, hybridPredictor, accuracyCalculator);

    return 0;
}
