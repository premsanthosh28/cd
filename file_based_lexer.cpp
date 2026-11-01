#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.txt");

    if (!fin) {
        cout << "File not found";
        return 0;
    }

    vector<string> keywords = {
        "int", "float", "char", "double",
        "if", "else", "while", "for",
        "return", "void"
    };

    string s((istreambuf_iterator<char>(fin)),
              istreambuf_iterator<char>());

    int i = 0;

    cout << left << setw(20) << "Lexeme"
         << "Token\n";

    while (i < (int)s.size()) {
        if (isspace(s[i])) {
            i++;
            continue;
        }

        if (isalpha(s[i]) || s[i] == '_') {
            string word;

            while (i < (int)s.size() &&
                  (isalnum(s[i]) || s[i] == '_'))
                word += s[i++];

            if (find(keywords.begin(), keywords.end(), word) != keywords.end())
                cout << left << setw(20) << word << "Keyword\n";
            else
                cout << left << setw(20) << word << "Identifier\n";
        }
        else if (isdigit(s[i])) {
            string num;

            while (i < (int)s.size() && isdigit(s[i]))
                num += s[i++];

            cout << left << setw(20) << num << "Number\n";
        }
        else if (string("+-*/%=<>!").find(s[i]) != string::npos) {
            string op(1, s[i++]);

            if (i < (int)s.size() && s[i] == '=') {
                op += s[i++];
            }

            cout << left << setw(20) << op << "Operator\n";
        }
        else if (string(";,(){}").find(s[i]) != string::npos) {
            string symbol(1, s[i++]);
            cout << left << setw(20) << symbol << "Special Symbol\n";
        }
        else {
            cout << left << setw(20) << s[i] << "Invalid Token\n";
            i++;
        }
    }

    fin.close();
    return 0;
}
