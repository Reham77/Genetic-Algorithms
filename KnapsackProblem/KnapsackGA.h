#include "../GeneticAlgorithm.cpp"


class KnapsackGA : public GeneticAlgorithm<int> {
private:
    vector<int> weight, benefit;
    int capacity;

    int getWeight(vector<int> &chromosome);
    bool isValid(int totalWeight) const;
    vector<int> getTakenIndices(vector<int> &chromosome) const;
    void fix(vector<int> &chromosome, int &currWeight);
    void validate(vector<int> &chromosome);

    void generateInitialPopulation() override;

    int calcFitnessFunction(vector<int> &chromosome) override;


    static bool shouldPerformMutation();
    void mutation(int idx) override; //perform bit flipping mutation

    void generateOffsprings() override;

public:
    KnapsackGA(int iterations , int populationSz, int numberOfGenes, int capacity,
               vector<int> &weight, vector<int> &benefit);

};

