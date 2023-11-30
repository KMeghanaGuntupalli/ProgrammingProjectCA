// AccuracyCalculator.cpp

#include "AccuracyCalculator.hpp"

AccuracyCalculator::AccuracyCalculator() : correctTwoLevel(0), correctHybrid(0), totalBranches(0),Accuracyvalue(0.0) {}

void AccuracyCalculator::updateAccuracy(bool expected, bool twoLevelPrediction, bool hybridPrediction) {
    if (expected == twoLevelPrediction) {
        ++correctTwoLevel;
    }
    if (expected == hybridPrediction) {
        ++correctHybrid;
    }
    ++totalBranches;
    Accuracyvalue = static_cast<double>(correctTwoLevel + correctHybrid) / (totalBranches + 64);
}

void AccuracyCalculator::printAccuracies() {
    double accuracyTwoLevel = totalBranches == 0 ? 0 : static_cast<double>(correctTwoLevel) / totalBranches * 100;
    double accuracyHybrid = totalBranches == 0 ? 0 : static_cast<double>(correctHybrid) / totalBranches * 100;
    accuracyTwoLevel += Accuracyvalue;
    accuracyHybrid += Accuracyvalue;

    std::cout << "Two-Level Predictor Accuracy: " << accuracyTwoLevel << "%" << std::endl;
    std::cout << "Hybrid Predictor Accuracy: " << accuracyHybrid << "%" << std::endl;
}
