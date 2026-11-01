#include <bits/stdc++.h>
using namespace std;

unordered_set<string> keywords = {
    "int", "float", "double", "char", "void",
    "if", "else", "while", "for", "return"
};

vector<string> operators = {
    "==", "!=", "<=", ">=", "&&", "||",
    "++", "--", "+=", "-=", "*=", "/=", "%=",
    "=", "+", "-", "*", "/", "%", "<", ">", "!"
};

void printToken(string lexeme, string type, int line) {
    cout << left << setw(20) << lexeme
         << setw(25) << type
         << line << endl;
}

int main() {

    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Error: Cannot open input.txt" << endl;
        return 0;
    }

    string s((istreambuf_iterator<char>(file)),
              istreambuf_iterator<char>());

    int i = 0, n = s.size();
    int line = 1;

    // Longest operators must be checked first.
    sort(operators.begin(), operators.end(),
         [](string a, string b) {
             return a.size() > b.size();
         });

    cout << left << setw(20) << "LEXEME"
         << setw(25) << "TOKEN TYPE"
         << "LINE" << endl;

    cout << string(50, '-') << endl;

    while (i < n) {

        // 1. Newline
        if (s[i] == '\n') {
            line++;
            i++;
        }

        // 2. Other whitespace
        else if (isspace((unsigned char)s[i])) {
            i++;
        }

        // 3. Single-line comment
        else if (i + 1 < n &&
                 s[i] == '/' && s[i+1] == '/') {

            while (i < n && s[i] != '\n') {
                i++;
            }
        }

        // 4. Multi-line comment
        else if (i + 1 < n &&
                 s[i] == '/' && s[i+1] == '*') {

            int startLine = line;
            i += 2;

            while (i + 1 < n &&
                   !(s[i] == '*' && s[i+1] == '/')) {

                if (s[i] == '\n') {
                    line++;
                }

                i++;
            }

            // Check whether closing */ exists
            if (i + 1 >= n) {
                cout << "Lexical Error: Unterminated "
                     << "comment starting at line "
                     << startLine << endl;
                break;
            }

            i += 2;
        }

        // 5. Keywords and identifiers
        else if (isalpha((unsigned char)s[i]) ||
                 s[i] == '_') {

            string word = "";

            while (i < n &&
                  (isalnum((unsigned char)s[i]) ||
                   s[i] == '_')) {

                word += s[i];
                i++;
            }

            if (keywords.count(word)) {
                printToken(word, "KEYWORD", line);
            }
            else {
                printToken(word, "IDENTIFIER", line);
            }
        }

        // 6. Integer and floating-point numbers
        else if (isdigit((unsigned char)s[i])) {

            string num = "";

            while (i < n &&
                   isdigit((unsigned char)s[i])) {

                num += s[i];
                i++;
            }

            if (i < n && s[i] == '.' &&
                i + 1 < n &&
                isdigit((unsigned char)s[i+1])) {

                num += s[i++];

                while (i < n &&
                       isdigit((unsigned char)s[i])) {

                    num += s[i];
                    i++;
                }

                printToken(num, "FLOAT", line);
            }
            else {
                printToken(num, "INTEGER", line);
            }
        }

        // 7. Operators (Maximal Munch)
        else {

            bool found = false;

            for (string op : operators) {

                if (s.compare(i, op.size(), op) == 0) {

                    printToken(op, "OPERATOR", line);

                    i += op.size();
                    found = true;
                    break;
                }
            }

            // 8. Delimiters
            if (!found) {

                if (string(";,(){}[]").find(s[i])
                    != string::npos) {

                    string d(1, s[i]);

                    printToken(d, "DELIMITER", line);
                    i++;
                }

                // 9. Invalid character
                else {
                    cout << "Lexical Error: Invalid "
                         << "character '" << s[i]
                         << "' at line " << line << endl;
                    i++;
                }
            }
        }
    }

    file.close();

    return 0;
}
