#ifndef GENETICALGORITHMS_KNAPSACKVALIDATION_H
#define GENETICALGORITHMS_KNAPSACKVALIDATION_H

#include "bits/stdc++.h"
using namespace std;

const int max_Elements = 100 , max_Size = 1000;

class KnapsackValidation {
     int dpSolution(int i, int rem, int numberOfItems, vector<int> &weight, vector<int> &benefit);

public:
     int dp[max_Elements][max_Size];
     int getOptimalSolution(int rem, int numberOfItems, vector<int> &weight,
                                  vector<int> &benefit);

};

#endif //GENETICALGORITHMS_KNAPSACKVALIDATION_H
