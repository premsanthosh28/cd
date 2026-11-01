#include <bits/stdc++.h>
using namespace std;

const int N = 8;
char buffer1[N + 1], buffer2[N + 1];
ifstream fin("input.txt");
bool first = true;

char getChar() {
    static int pos = 0;
    static bool second = false;

    if (pos == N) {
        if (!second) {
            fin.read(buffer2, N);
            buffer2[fin.gcount()] = '\0';
            second = true;
        } else {
            fin.read(buffer1, N);
            buffer1[fin.gcount()] = '\0';
            second = false;
        }
        pos = 0;
    }

    char c = second ? buffer2[pos] : buffer1[pos];

    if (c == '\0') return EOF;

    pos++;
    return c;
}

int main() {
    if (!fin) {
        cout << "File not found";
        return 0;
    }

    fin.read(buffer1, N);
    buffer1[fin.gcount()] = '\0';

    vector<string> keywords = {
        "int", "float", "char", "double",
        "if", "else", "while", "return"
    };

    string word;
    char c;

    cout << "Lexemes:\n";

    while ((c = getChar()) != EOF) {
        if (isalnum(c) || c == '_') {
            word += c;
        } else {
            if (!word.empty()) {
                if (find(keywords.begin(), keywords.end(), word) != keywords.end())
                    cout << word << " : Keyword\n";
                else if (isdigit(word[0]))
                    cout << word << " : Number\n";
                else
                    cout << word << " : Identifier\n";

                word.clear();
            }

            if (!isspace(c))
                cout << c << " : Special Symbol\n";
        }
    }

    if (!word.empty()) {
        if (find(keywords.begin(), keywords.end(), word) != keywords.end())
            cout << word << " : Keyword\n";
        else if (isdigit(word[0]))
            cout << word << " : Number\n";
        else
            cout << word << " : Identifier\n";
    }

    fin.close();
    return 0;
}
