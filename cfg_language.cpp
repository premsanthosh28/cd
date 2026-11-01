#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;

    cout << "Enter n: ";
    cin >> n;

    if (n <= 0) {
        cout << "n must be greater than 0";
        return 0;
    }

    string result = "";

    for (int i = 0; i < n; i++) {
        result += "aab";
    }

    cout << "\nCFG:\n";
    cout << "S -> aabS | aab\n";

    cout << "\nGenerated String:\n";
    cout << result << endl;

    cout << "\nLanguage Pattern:\n";
    cout << "L = {(aab)^n | n > 0}\n";

    return 0;
}
