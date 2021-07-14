#ifndef UNTITLED7_CURVEFITTINGGA_CPP
#define UNTITLED7_CURVEFITTINGGA_CPP

#include "CurveFittingGA.h"

CurveFittingGA::CurveFittingGA(int iterations, int populationSz, int numberOfGenes, vector<Point> &points,
                               int numberOfPoints)
        : GeneticAlgorithm<double>(populationSz, numberOfGenes, iterations) {
    this->points = points;
    this->numberOfPoints = numberOfPoints;
}



#endif