#include "GeneticAlgorithm.cpp"
#include "Point.h"


class CurveFittingGA : public GeneticAlgorithm<double> {

private:
    int numberOfPoints;
    vector<Point> points;

    void generateInitialPopulation() override;

    double calcFitnessFunction(vector<double> &chromosome) override;

    void mutation(int idx) override; //perform non-uniform mutation

    void generateOffsprings() override;


public:
    CurveFittingGA(int iterations, int populationSz, int numberOfGenes, vector<Point> &points, int numberOfPoints);

};


