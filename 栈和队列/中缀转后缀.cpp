#include <bits/stdc++.h>
using namespace std;

char stk[1000];
int top = -1;

int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}
bool leftAssoc(char op) {
    return op != '^';
}

string solve(const string &s) {
    string res;
    top = -1;
    for (char c : s) {
        if (isalpha(c) || isdigit(c)) res += c;
        else if (c == '(') stk[++top] = c;
        else if (c == ')') {
            while (top >= 0 && stk[top] != '(') res += stk[top--];
            if (top >= 0 && stk[top] == '(') top--;
        } else {
            while (top >= 0 && stk[top] != '(' &&
                   (prec(stk[top]) > prec(c) ||
                    (prec(stk[top]) == prec(c) && leftAssoc(c))))
                res += stk[top--];
            stk[++top] = c;
        }
    }
    while (top >= 0) res += stk[top--];
    return res;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string t;
        char c;
        while (cin.get(c)) {
            if (c == '#') break;
            if (!isspace(c)) t += c;
        }
        cout << solve(t) << "\n";
    }
}