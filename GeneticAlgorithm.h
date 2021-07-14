
#include "bits/stdc++.h"

using namespace std;
const int LowerBound = -10, UpperBound = 10;
const double crossOverProb = 0.7, mutationProb = 0.015;

template<class GeneType>
struct Chromosome {
    vector<GeneType> chromosome;
    GeneType fitness;
};

template<class GeneType>
class GeneticAlgorithm {
protected:
    vector<Chromosome<GeneType>> population, offsprings;
    vector<GeneType> fitnessCum;
    int offspringIdx, numberOfGenes, populationSz, iterations , currIter;

    void initialize();
    virtual void generateInitialPopulation() = 0;

    virtual GeneType calcFitnessFunction(vector<GeneType> &chromosome) = 0;
    void calcPopulationFitness();
    void calcFitnessCum();

    int selection();
    int selection(int prevSelected);

    bool shouldPerformCrossOver();
    void crossOver(int selectedChromosome1, int selectedChromosome2);

    virtual void mutation(int idx) = 0;
    virtual void generateOffsprings() = 0;

    void replacement();

public:
    GeneticAlgorithm(int populationSz, int numberOfGenes ,int iterations);
    pair<vector<GeneType>, GeneType> run();
};


