#ifndef UNTITLED7_GA_CPP
#define UNTITLED7_GA_CPP

#include "GeneticAlgorithm.h"

template<class GeneType>
GeneticAlgorithm<GeneType>::GeneticAlgorithm(int populationSz, int numberOfGenes, int iterations) {
    this->populationSz = populationSz;
    this->numberOfGenes = numberOfGenes;
    this->iterations = iterations;

    population.resize(populationSz + 2);
    offsprings.resize(populationSz + 2);

    currIter = 0;
}

template<class GeneType>
void GeneticAlgorithm<GeneType>::initialize() {
    offspringIdx = 0;
}

template<class GeneType>
void GeneticAlgorithm<GeneType>::calcPopulationFitness() {
    for (int i = 0; i < populationSz; ++i) {
        GeneType totalFitness = calcFitnessFunction(population[i].chromosome);
        population[i].fitness = totalFitness;
    }
}

template<class GeneType>
void GeneticAlgorithm<GeneType>::calcFitnessCum() {
    fitnessCum.clear();
    fitnessCum.resize(populationSz);

    for (int i = 0; i < populationSz; ++i) {
        fitnessCum[i] = population[i].fitness;
        if (i)
            fitnessCum[i] += fitnessCum[i - 1];
    }
}

template<class GeneType>
int GeneticAlgorithm<GeneType>::selection() {
    if (fitnessCum.back() == 0)
        return 0;
    //choose a random fitness from 0 to fitnessCumulative[n - 1]
    double randomFitness = fmod(rand(), fitnessCum.back());

    //get the Index of the chromosome which has the smallest value larger than the randomized fitness
    int geneIdx = upper_bound(fitnessCum.begin(), fitnessCum.end(), randomFitness) - fitnessCum.begin();
    return geneIdx;
}

template<class GeneType>
int GeneticAlgorithm<GeneType>::selection(int prevSelected) {
    if (fitnessCum.back() - population[prevSelected].fitness == 0)return 0;

    //choose a random fitness value from 0 to fitnessCumulative[n - 1] - previously chosen chromosome's fitness value
    double randomGene = fmod(rand(), (fitnessCum.back() - population[prevSelected].fitness));

    //if the randomized fitness is in the same range as the previously selected chromosome's fitness then shift it
    if (randomGene < fitnessCum[prevSelected] && (!prevSelected || randomGene >= fitnessCum[prevSelected - 1]))
        randomGene += population[prevSelected].fitness;

    //get the Index of the chromosome which has the smallest value larger than the randomized fitness
    int geneIdx = upper_bound(fitnessCum.begin(), fitnessCum.end(), randomGene) - fitnessCum.begin();
    return geneIdx;
}

template<class GeneType>
bool GeneticAlgorithm<GeneType>::shouldPerformCrossOver() {
    double probability = (double) rand() / RAND_MAX;
    return (probability <= crossOverProb);
}


template<class GeneType>
void GeneticAlgorithm<GeneType>::crossOver(int selectedChromosome1, int selectedChromosome2) {
    offsprings[offspringIdx] = population[selectedChromosome1];
    offsprings[offspringIdx + 1] = population[selectedChromosome2];

    if (shouldPerformCrossOver()) {
        int point = rand() % (numberOfGenes - 1);

        for (int i = point; i < numberOfGenes; ++i) {
            offsprings[offspringIdx].chromosome[i] = population[selectedChromosome2].chromosome[i];
            offsprings[offspringIdx + 1].chromosome[i] = population[selectedChromosome1].chromosome[i];
        }
    }
    offspringIdx += 2;
}

template<class GeneType>
void GeneticAlgorithm<GeneType>::replacement() {
    //calculate the fitness for the offsprings
    for (int i = 0; i < offsprings.size(); ++i) {
        offsprings[i].fitness = calcFitnessFunction(offsprings[i].chromosome);
    }
    //merge the population and the offsprings
    offsprings.insert(offsprings.end(), population.begin(), population.end());

    //sort the merged vector
    sort(offsprings.begin(), offsprings.end(), [&](Chromosome<GeneType> &a, Chromosome<GeneType> &b) {
        return a.fitness > b.fitness;
    });
    //choose top K
    offsprings.erase(offsprings.begin() + populationSz, offsprings.end());

    //set new population to be the top K
    population = offsprings;
}


template<class GeneType>
pair<vector<GeneType>, GeneType> GeneticAlgorithm<GeneType>::run() {

    initialize();
    generateInitialPopulation();
    calcPopulationFitness();

    for (int i = 0; i < iterations; ++i) {
        calcFitnessCum();

        while (offspringIdx < populationSz) {
            generateOffsprings();
        }
        //mix replacement - sort and take the best k to be the new population
        replacement();
        initialize();

        currIter++;
    }
    return {offsprings[0].chromosome, offsprings[0].fitness};
}

#endif