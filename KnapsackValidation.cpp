#include "KnapsackValidation.h"

int KnapsackValidation::dpSolution(int i, int rem, int numberOfItems, vector<int> &weight,
                                   vector<int> &benefit) {
    if (rem < 0)return -1e9;
    if (i == numberOfItems)return 0;
    int &ret = dp[i][rem];
    if (~ret)return ret;
    ret = 0;
    ret = max(dpSolution(i + 1, rem, numberOfItems, weight, benefit),
              dpSolution(i + 1, rem - weight[i], numberOfItems, weight, benefit) + benefit[i]);
    return ret;
}

int KnapsackValidation::getOptimalSolution(int rem, int numberOfItems, vector<int> &weight,
                                           vector<int> &benefit) {
    memset(dp , -1 , sizeof(dp));
    return dpSolution(0 , rem , numberOfItems , weight , benefit);
}
