#include "bits/stdc++.h"

#include "KnapsackProblem/KnapsackGA.h"
#include "CurveFittingProblem//CurveFittingGA.h"
#include "KnapsackProblem/KnapsackValidation.h"

using namespace std;

const int pop_sz = 100;

/*
 * Function to get the inputFileSample.txt of the Knapsack problem
 */
void KnapsackGAInput(int test, double &AccuracyRatio) {

    int numberOfItems, capacity;
    vector<int> weight, benefit;

    cin >> numberOfItems >> capacity;
    weight.resize(numberOfItems), benefit.resize(numberOfItems);
    for (int i = 0; i < numberOfItems; i++) {
        cin >> weight[i] >> benefit[i];
    }
    KnapsackGA testCase(15000, pop_sz, numberOfItems, capacity, weight, benefit);
    vector<int> ans = testCase.run().first;

    cout << "Case #" << test << "\n";
    int GASolution = 0;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i])
            GASolution += benefit[i];
    }
    int DpSolution = KnapsackValidation().getOptimalSolution(capacity, numberOfItems, weight, benefit); //get DP solution

    cout << "DP Solution: " << DpSolution << " GA Solution: " << GASolution << "\n" << endl;

    cout << "Taken Items:" << "\n";
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i])
            cout << weight[i] << " " << benefit[i] << "\n";
    }
    cout << "\n";
    AccuracyRatio += (GASolution / (double) DpSolution);

}

/*
 * Function to get the inputFileSample.txt of the Curve Fitting problem
 */
void CurveFittingInput(int test) {
    vector<Point> points;
    int numberOfPoints, degree;
    cin >> numberOfPoints >> degree;
    for (int i = 0; i < numberOfPoints; ++i) {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    CurveFittingGA testCase(10000, pop_sz, degree + 1, points, numberOfPoints);
    pair<vector<double>, double> x = testCase.run();

    cout << "Case #" << test << "\n";
    cout << "MSE = " << fixed << 1.00 / x.second << "\n";

    cout << "Coefficients:" << "\n";
    for (int i = 0; i < x.first.size(); ++i) {
        cout << fixed << setprecision(5) << x.first[i] << "X^" << i << " " << "+\n"[i + 1 == x.first.size()]
             << " \n"[i + 1 == x.first.size()];

    }

}

int main() {

    freopen("inputFileSample.txt", "r", stdin);
    freopen("outputFile.txt", "w", stdout);

    srand(time(NULL));
    cout << "Press 1 for Knapsack algorithm\nPress 2 for CurveFittingProblem algorithm" << "\n";
    int selection;
    cin >> selection;

    int test, currTest = 1;
    double accuracyRatio = 0;
    cin >> test;
    while (test--) {
        if (selection == 1)
        {
            KnapsackGAInput(currTest, accuracyRatio);

            if (test == 0) {
                cout << "Accuracy: " << accuracyRatio / currTest * 100 << "\n";
            }

        } else if (selection == 2)
        {
            CurveFittingInput(currTest);
        }
        currTest++;
    }
    return 0;
}
