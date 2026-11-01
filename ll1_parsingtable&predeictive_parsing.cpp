#include <bits/stdc++.h>
using namespace std;

map<pair<char,char>,string> table;

int main() {
    table[{'S','a'}] = "aABe";
    table[{'A','b'}] = "bAc";
    table[{'A','d'}] = "d";
    table[{'B','f'}] = "f";
    table[{'B','e'}] = "";

    string input;
    cout << "Enter input string: ";
    cin >> input;
    input += '$';

    stack<char> st;
    st.push('$');
    st.push('S');

    int i = 0;

    cout << "\nStack\tInput\tAction\n";

    while (!st.empty()) {
        string current;
        stack<char> temp = st;

        while (!temp.empty()) {
            current += temp.top();
            temp.pop();
        }

        char top = st.top();
        char look = input[i];

        cout << current << "\t" << input.substr(i) << "\t";

        if (top == look) {
            st.pop();
            i++;
            cout << "Match " << look << "\n";
        }
        else if (top == '$') {
            break;
        }
        else if (isupper(top)) {
            if (table.find({top,look}) == table.end()) {
                cout << "Error\n";
                return 0;
            }

            string prod = table[{top,look}];
            st.pop();

            for (int j = (int)prod.size() - 1; j >= 0; j--)
                st.push(prod[j]);

            cout << top << " -> "
                 << (prod.empty() ? "epsilon" : prod) << "\n";
        }
        else {
            cout << "Error\n";
            return 0;
        }
    }

    if (st.empty() && i == (int)input.size())
        cout << "\nString Accepted\n";
    else
        cout << "\nString Rejected\n";

    return 0;
}
