#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;

    cout << "Enter expression: ";
    getline(cin, s);

    vector<string> operators = {
        "==", "!=", "<=", ">=", "++", "--",
        "&&", "||", "+", "-", "*", "/", "%",
        "=", "<", ">"
    };

    int i = 0;

    cout << "\nLexeme\t\tToken\n";

    while (i < (int)s.size()) {

        if (isspace(s[i])) {
            i++;
            continue;
        }

        if (isalpha(s[i]) || s[i] == '_') {
            string word;

            while (i < (int)s.size() &&
                  (isalnum(s[i]) || s[i] == '_')) {
                word += s[i++];
            }

            cout << word << "\t\tIdentifier\n";
        }

        else if (isdigit(s[i])) {
            string num;

            while (i < (int)s.size() &&
                  (isdigit(s[i]) || s[i] == '.')) {
                num += s[i++];
            }

            cout << num << "\t\tNumber\n";
        }

        else {
            string matched = "";

            for (string op : operators) {
                if (s.substr(i, op.size()) == op &&
                    op.size() > matched.size()) {
                    matched = op;
                }
            }

            if (!matched.empty()) {
                cout << matched << "\t\tOperator\n";
                i += matched.size();
            }
            else if (string(";,(){}").find(s[i]) != string::npos) {
                cout << s[i] << "\t\tSpecial Symbol\n";
                i++;
            }
            else {
                cout << s[i] << "\t\tInvalid Token\n";
                i++;
            }
        }
    }

    return 0;
}
