#include <bits/stdc++.h>
using namespace std;

struct Token {
    string type, value;
};

struct Quad {
    string op, arg1, arg2, result;
};

vector<Token> tokens;
vector<Quad> code;

int pos = 0;
int tempCount = 0;

string newTemp() {
    return "t" + to_string(++tempCount);
}

void tokenize(string s) {
    int i = 0;

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

            tokens.push_back({"ID", word});
        }
        else if (isdigit(s[i])) {
            string num;

            while (i < (int)s.size() &&
                  (isdigit(s[i]) || s[i] == '.'))
                num += s[i++];

            tokens.push_back({"NUM", num});
        }
        else {
            tokens.push_back({"OP", string(1, s[i++])});
        }
    }

    tokens.push_back({"END", "$"});
}

string expression();

string factor() {
    if (tokens[pos].type == "ID" ||
        tokens[pos].type == "NUM") {
        return tokens[pos++].value;
    }

    if (tokens[pos].value == "(") {
        pos++;

        string result = expression();

        if (tokens[pos].value != ")")
            throw runtime_error("Missing closing parenthesis");

        pos++;
        return result;
    }

    throw runtime_error("Invalid expression");
}

string term() {
    string left = factor();

    while (tokens[pos].value == "*" ||
           tokens[pos].value == "/") {

        string op = tokens[pos++].value;
        string right = factor();

        string temp = newTemp();

        code.push_back({op, left, right, temp});

        left = temp;
    }

    return left;
}

string expression() {
    string left = term();

    while (tokens[pos].value == "+" ||
           tokens[pos].value == "-") {

        string op = tokens[pos++].value;
        string right = term();

        string temp = newTemp();

        code.push_back({op, left, right, temp});

        left = temp;
    }

    return left;
}

int main() {
    string s;

    cout << "Enter expression: ";
    getline(cin, s);

    try {
        tokenize(s);

        string lhs;

        if (tokens[0].type == "ID" &&
            tokens[1].value == "=") {

            lhs = tokens[0].value;
            pos = 2;
        }

        string result = expression();

        if (tokens[pos].value != "$")
            throw runtime_error("Invalid syntax");

        if (!lhs.empty())
            code.push_back({"=", result, "-", lhs});

        cout << "\nThree Address Code:\n";

        for (auto q : code) {
            if (q.op == "=")
                cout << q.result << " = " << q.arg1 << "\n";
            else
                cout << q.result << " = "
                     << q.arg1 << " "
                     << q.op << " "
                     << q.arg2 << "\n";
        }

        cout << "\nQuadruple Representation:\n";
        cout << "Op\tArg1\tArg2\tResult\n";

        for (auto q : code) {
            cout << q.op << "\t"
                 << q.arg1 << "\t"
                 << q.arg2 << "\t"
                 << q.result << "\n";
        }

        cout << "\nTriple Representation:\n";
        cout << "Index\tOp\tArg1\tArg2\n";

        for (int i = 0; i < (int)code.size(); i++) {
            string a = code[i].arg1;
            string b = code[i].arg2;

            for (int j = 0; j < i; j++) {
                if (a == code[j].result)
                    a = "(" + to_string(j) + ")";

                if (b == code[j].result)
                    b = "(" + to_string(j) + ")";
            }

            cout << i << "\t"
                 << code[i].op << "\t"
                 << a << "\t"
                 << b << "\n";
        }
    }
    catch (exception &e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
