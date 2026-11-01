#include <bits/stdc++.h>
using namespace std;

struct Production {
    char lhs;
    string rhs;
};

vector<Production> p = {
    {'S', "CC"},
    {'C', "cC"},
    {'C', "d"}
};

int actionTable[7][4] = {
    {0,0,3,4},
    {0,0,0,0},
    {0,0,3,4},
    {0,0,0,0},
    {0,0,3,4},
    {0,0,0,0},
    {0,0,0,0}
};

int main() {
    string input;

    cout << "Enter input string: ";
    cin >> input;
    input += '$';

    map<pair<int,char>,string> action = {
        {{0,'c'},"s3"}, {{0,'d'},"s4"},
        {{1,'$'},"acc"},
        {{2,'c'},"s3"}, {{2,'d'},"s4"},
        {{3,'c'},"s3"}, {{3,'d'},"s4"},
        {{4,'c'},"r3"}, {{4,'d'},"r3"},
        {{4,'$'},"r3"},
        {{5,'c'},"r1"}, {{5,'d'},"r1"},
        {{5,'$'},"r1"},
        {{6,'c'},"r2"}, {{6,'d'},"r2"},
        {{6,'$'},"r2"}
    };

    map<pair<int,char>,int> go = {
        {{0,'S'},1}, {{0,'C'},2},
        {{2,'C'},5}, {{3,'C'},6}
    };

    stack<int> st;
    st.push(0);

    int i = 0;

    cout << "\nParsing:\n";

    while (true) {
        int state = st.top();
        char symbol = input[i];

        if (!action.count({state,symbol})) {
            cout << "String Rejected\n";
            return 0;
        }

        string act = action[{state,symbol}];

        cout << "State: " << state << " Input: "
             << input.substr(i) << " Action: " << act << "\n";

        if (act == "acc") {
            cout << "String Accepted\n";
            break;
        }

        if (act[0] == 's') {
            st.push(stoi(act.substr(1)));
            i++;
        }
        else if (act[0] == 'r') {
            int r = stoi(act.substr(1));
            int len = p[r-1].rhs.size();

            for (int j = 0; j < len; j++)
                st.pop();

            int next = go[{st.top(),p[r-1].lhs}];
            st.push(next);
        }
    }

    return 0;
}
