#include <bits/stdc++.h>
using namespace std;

enum Type {
    INT, FLOAT, BOOL, UNKNOWN
};

string typeName(Type t) {
    if (t == INT) return "int";
    if (t == FLOAT) return "float";
    if (t == BOOL) return "bool";
    return "unknown";
}

struct Token {
    string value;
    string type;
};

struct ASTNode {
    string value;
    Type type;
    ASTNode *left, *right;

    ASTNode(string v, Type t = UNKNOWN) {
        value = v;
        type = t;
        left = right = nullptr;
    }
};

map<string, Type> symbolTable;
vector<Token> tokens;
int pos;

void tokenize(string s) {
    tokens.clear();

    for (int i = 0; i < (int)s.size();) {
        if (isspace(s[i])) {
            i++;
        }
        else if (isalpha(s[i]) || s[i] == '_') {
            string word;

            while (i < (int)s.size() &&
                   (isalnum(s[i]) || s[i] == '_'))
                word += s[i++];

            tokens.push_back({word, "ID"});
        }
        else if (isdigit(s[i])) {
            string num;

            while (i < (int)s.size() &&
                   (isdigit(s[i]) || s[i] == '.'))
                num += s[i++];

            tokens.push_back({num, "NUM"});
        }
        else {
            tokens.push_back({string(1, s[i]), "OP"});
            i++;
        }
    }

    tokens.push_back({"$", "END"});
    pos = 0;
}

ASTNode* expression();

ASTNode* factor() {
    if (tokens[pos].type == "NUM") {
        string value = tokens[pos++].value;

        Type t = value.find('.') == string::npos ? INT : FLOAT;

        return new ASTNode(value, t);
    }

    if (tokens[pos].value == "true" ||
        tokens[pos].value == "false") {
        return new ASTNode(tokens[pos++].value, BOOL);
    }

    if (tokens[pos].type == "ID") {
        return new ASTNode(tokens[pos++].value);
    }

    if (tokens[pos].value == "(") {
        pos++;

        ASTNode* node = expression();

        if (tokens[pos].value != ")")
            throw runtime_error("Missing closing parenthesis");

        pos++;
        return node;
    }

    throw runtime_error("Invalid expression");
}

ASTNode* term() {
    ASTNode* left = factor();

    while (tokens[pos].value == "*" ||
           tokens[pos].value == "/") {

        string op = tokens[pos++].value;
        ASTNode* right = factor();

        ASTNode* node = new ASTNode(op);
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

ASTNode* expression() {
    ASTNode* left = term();

    while (tokens[pos].value == "+" ||
           tokens[pos].value == "-") {

        string op = tokens[pos++].value;
        ASTNode* right = term();

        ASTNode* node = new ASTNode(op);
        node->left = left;
        node->right = right;

        left = node;
    }

    return left;
}

Type check(ASTNode* node) {
    if (node->left == nullptr && node->right == nullptr) {
        if (node->type != UNKNOWN)
            return node->type;

        if (symbolTable.count(node->value))
            return symbolTable[node->value];

        cout << "Semantic Error: Undeclared variable "
             << node->value << "\n";

        return UNKNOWN;
    }

    Type left = check(node->left);
    Type right = check(node->right);

    if (left == UNKNOWN || right == UNKNOWN)
        return UNKNOWN;

    if ((left != INT && left != FLOAT) ||
        (right != INT && right != FLOAT)) {

        cout << "Semantic Error: Invalid operand types\n";
        return UNKNOWN;
    }

    if (left == FLOAT || right == FLOAT)
        return FLOAT;

    return INT;
}

int main() {
    int n;

    cout << "Enter number of statements: ";
    cin >> n;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        string s;

        cout << "\nEnter statement " << i + 1 << ": ";
        getline(cin, s);

        try {
            tokenize(s);

            Type declaredType = UNKNOWN;

            if (tokens[pos].value == "int")
                declaredType = INT;
            else if (tokens[pos].value == "float")
                declaredType = FLOAT;
            else if (tokens[pos].value == "bool")
                declaredType = BOOL;

            bool declaration = declaredType != UNKNOWN;

            if (declaration)
                pos++;

            if (tokens[pos].type != "ID")
                throw runtime_error("Invalid variable name");

            string name = tokens[pos++].value;

            if (declaration && symbolTable.count(name))
                throw runtime_error("Variable already declared");

            if (!declaration && !symbolTable.count(name)) {
                cout << "Semantic Error: Undeclared variable "
                     << name << "\n";
                continue;
            }

            if (tokens[pos].value != "=")
                throw runtime_error("Expected assignment operator");

            pos++;

            ASTNode* root = expression();

            if (tokens[pos].value == ";")
                pos++;

            if (tokens[pos].value != "$")
                throw runtime_error("Invalid syntax");

            Type exprType = check(root);

            if (exprType == UNKNOWN)
                continue;

            Type target = declaration ?
                          declaredType : symbolTable[name];

            if (target == BOOL && exprType != BOOL) {
                cout << "Type Error: Expected bool value\n";
                continue;
            }

            if (target != BOOL && exprType == BOOL) {
                cout << "Type Error: Cannot assign bool to "
                     << typeName(target) << "\n";
                continue;
            }

            if (target == INT && exprType == FLOAT) {
                cout << "Type Error: Cannot assign float to int\n";
                continue;
            }

            if (declaration)
                symbolTable[name] = declaredType;

            cout << "Valid Statement\n";
            cout << "Variable: " << name << "\n";
            cout << "Expression Type: " << typeName(exprType) << "\n";
            cout << "Variable Type: " << typeName(target) << "\n";
        }
        catch (exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    cout << "\nSymbol Table:\n";

    for (auto x : symbolTable)
        cout << x.first << " : " << typeName(x.second) << "\n";

    return 0;
}
