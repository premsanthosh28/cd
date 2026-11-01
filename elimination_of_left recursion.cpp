#include <bits/stdc++.h>
using namespace std;

void removeLeftRecursion(char nt, string alpha, string beta) {
    cout << nt << " -> " << beta << nt << "'\n";
    cout << nt << "' -> " << alpha << nt << "' | epsilon\n";
}

int main() {
    cout << "Original Grammar:\n";
    cout << "E -> E+T | T\n";
    cout << "T -> T*F | F\n";
    cout << "F -> (E) | id\n";

    cout << "\nAfter Removing Left Recursion:\n";

    removeLeftRecursion('E', "+T", "T");
    removeLeftRecursion('T', "*F", "F");

    cout << "F -> (E) | id\n";

    return 0;
}
