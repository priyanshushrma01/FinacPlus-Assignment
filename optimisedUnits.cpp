#include <bits/stdc++.h>
using namespace std;

// Returns minimum number of units needed to make "amount"
int findMinUnits(int amount, const vector<int>& units) {
    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int u : units) {
            if (u <= i && dp[i - u] != INF) {
                dp[i] = min(dp[i], dp[i - u] + 1);
            }
        }
    }
    return dp[amount];
}

int main() {
    // example
    vector<int> units = {1, 2, 5, 10, 20, 50};

    int maxValue = 99;
    long long totalUnitsUsed = 0;

    cout << "Units used: ";
    for (int u : units) cout << u << " ";
    cout << "\n\n";

    cout << "Value : Min units used\n";
    cout << "----------------------\n";

    for (int value = 1; value <= maxValue; value++) {
        int unitsUsed = findMinUnits(value, units);
        totalUnitsUsed += unitsUsed;
        cout << setw(3) << value << "   : " << unitsUsed << "\n";
    }

    double average = (double)totalUnitsUsed / maxValue;
    cout << "\nAverage units used (1 to " << maxValue << ") = "
         << fixed << setprecision(2) << average << "\n";

    return 0;
}
