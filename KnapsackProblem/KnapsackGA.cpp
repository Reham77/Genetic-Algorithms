#ifndef UNTITLED7_KNAPSACKGA_CPP
#define UNTITLED7_KNAPSACKGA_CPP

#include "KnapsackGA.h"

KnapsackGA::KnapsackGA(int iterations, int populationSz, int numberOfGenes, int capacity,
                       vector<int> &weight, vector<int> &benefit) : GeneticAlgorithm(populationSz, numberOfGenes,
                                                                                     iterations) {
    this->capacity = capacity;
    this->weight = weight;
    this->benefit = benefit;
}

int KnapsackGA::getWeight(vector<int> &chromosome) {
    int totalWeight = 0;
    for (int i = 0; i < chromosome.size(); ++i) {
        totalWeight += (chromosome[i] * weight[i]);
    }
    return totalWeight;
}

bool KnapsackGA::isValid(int totalWeight) const {
    return (totalWeight <= capacity);
}


vector<int> KnapsackGA::getTakenIndices(vector<int> &chromosome) const {
    vector<int> indices;
    for (int i = 0; i < numberOfGenes; ++i) {
        if (chromosome[i])
            indices.push_back(i);
    }
    shuffle(indices.begin(), indices.end(),
            default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
    return indices;
}

void KnapsackGA::fix(vector<int> &chromosome, int &currWeight) {
    vector<int> indices = getTakenIndices(chromosome);
    while (currWeight > capacity) {
        int currIdx = indices.back();
        indices.pop_back();
        chromosome[currIdx] = false, currWeight -= weight[currIdx];
    }
}

void KnapsackGA::validate(vector<int> &chromosome) {
    int currWeight = getWeight(chromosome);
    if (!isValid(currWeight))
        fix(chromosome, currWeight);
}

void KnapsackGA::generateInitialPopulation() {
    for (int i = 0; i < populationSz; ++i) {
        population[i].chromosome.resize(numberOfGenes);
        for (int j = 0; j < numberOfGenes; ++j) {
            int random = rand() % 10;
            if (random < 5)
                population[i].chromosome[j] = true;
        }
        validate(population[i].chromosome);
    }
}

int KnapsackGA::calcFitnessFunction(vector<int> &chromosome) {
    if (chromosome.empty())
        return 0;

    int totalFitness = 0;
    for (int j = 0; j < numberOfGenes; ++j) {
        totalFitness += (chromosome[j] * benefit[j]);
    }
    return totalFitness;
}

bool KnapsackGA::shouldPerformMutation() {
    double probability = (double) rand() / RAND_MAX;
    return (probability <= mutationProb);

}

void KnapsackGA::mutation(int idx) {
    for (int i = 0; i < numberOfGenes; ++i) {
        if (shouldPerformMutation()) {
            offsprings[idx].chromosome[i] = 1 - offsprings[idx].chromosome[i];
        }
    }
    validate(offsprings[idx].chromosome);
}

void KnapsackGA::generateOffsprings() {

    int selectedChromosome1 = selection();
    int selectedChromosome2 = selection(selectedChromosome1);

    crossOver(selectedChromosome1, selectedChromosome2);

    validate(offsprings[offspringIdx - 1].chromosome);
    validate(offsprings[offspringIdx - 2].chromosome);

    mutation(offspringIdx - 1);
    mutation(offspringIdx - 2);

}
#endif