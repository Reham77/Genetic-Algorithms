#ifndef UNTITLED7_CURVEFITTINGGA_CPP
#define UNTITLED7_CURVEFITTINGGA_CPP

#include "CurveFittingGA.h"

CurveFittingGA::CurveFittingGA(int iterations, int populationSz, int numberOfGenes, vector<Point> &points,
                               int numberOfPoints)
        : GeneticAlgorithm<double>(populationSz, numberOfGenes, iterations) {
    this->points = points;
    this->numberOfPoints = numberOfPoints;
}

void CurveFittingGA::generateInitialPopulation() {
    for (int i = 0; i < populationSz; ++i) {
        population[i].chromosome.resize(numberOfGenes);
        for (int j = 0; j < numberOfGenes; ++j) {
            double random = LowerBound + (UpperBound - LowerBound) * rand() / (double) RAND_MAX;
            population[i].chromosome[j] = random;
        }
    }
}
double CurveFittingGA::calcFitnessFunction(vector<double> &chromosome) {
    if (chromosome.size() == 0)
        return 0;

    double MSE = 0;
    for (int j = 0; j < numberOfPoints; ++j) {
        double yPredicted = 0;
        for (int k = 0; k < numberOfGenes; ++k) {
            yPredicted += chromosome[k] * pow(points[j].x, k);
        }
        MSE += ((points[j].y - yPredicted) * (points[j].y - yPredicted));
    }
    MSE = numberOfPoints / MSE;
    return MSE;
}


void CurveFittingGA::mutation(int idx) {
    for (int i = 0; i < numberOfGenes; ++i) {
        double upper = UpperBound - offsprings[idx].chromosome[i];
        double lower = offsprings[idx].chromosome[i] - LowerBound;

        double bound = (double) rand() / RAND_MAX;
        double y = ((bound > 0.5) ? upper : lower);

        double r = (double) rand() / RAND_MAX;
        double b = 1.00 + (rand() / (double) RAND_MAX) * 4.00; // dependency factor

        double mutationAmount = y * (1 - pow(r, pow(1 - (double) currIter / iterations, b)));
        offsprings[idx].chromosome[i] += (bound > 0.5 ? 1 : -1) * mutationAmount;
    }

}

void CurveFittingGA::generateOffsprings() {

    int selectedChromosome1 = selection();
    int selectedChromosome2 = selection(selectedChromosome1);

    crossOver(selectedChromosome1, selectedChromosome2);

    mutation(offspringIdx - 1);
    mutation(offspringIdx - 2);

}

#endif