#include<bits/stdc++.h>
using namespace std;

map<string, long long> variables;

int get_precedence(char op) {
    if (op == '^') return 4;
    if (op == '~') return 3; 
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; 
}
void apply_op(stack<long long>& values, stack<char>& ops) {
    if (ops.empty()) throw runtime_error("Invalid expression");
    
    char op = ops.top();
    ops.pop();

    if (op == '~') { 
        if (values.empty()) throw runtime_error("Invalid expression");
        long long val = values.top();
        values.pop();
        values.push(-val);
    } else { 
        if (values.size() < 2) throw runtime_error("Invalid expression");
        long long r = values.top();
        values.pop();
        long long l = values.top();
        values.pop();

        if (op == '+') values.push(l + r);
        else if (op == '-') values.push(l - r);
        else if (op == '*') values.push(l * r);
        else if (op == '/') {
            if (r == 0) throw runtime_error("Divide 0.");
            values.push(l / r);
        } else if (op == '%') {
            if (r == 0) throw runtime_error("Divide 0.");
            values.push(l % r);
        } else if (op == '^') {
            values.push(static_cast<long long>(pow(l, r)));
        }
    }
}

long long evaluate(const string& expression) {
    stack<long long> values;
    stack<char> ops;
    bool can_be_unary = true; 

    for (int i = 0; i < expression.length(); ++i) {
        if (isspace(expression[i])) continue;

        if (isalpha(expression[i])) {
            string var;
            while (i < expression.length() && isalpha(expression[i])) {
                var += expression[i++];
            }
            i--;
            values.push(variables[var]);
            can_be_unary = false;
        } else if (isdigit(expression[i])) {
            long long num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i++] - '0');
            }
            i--;
            values.push(num);
            can_be_unary = false;
        } else if (expression[i] == '(') {
            ops.push('(');
            can_be_unary = true;
        } else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                apply_op(values, ops);
            }
            if (!ops.empty()) ops.pop();
            can_be_unary = false;
        } else {
            char op = expression[i];
            if ((op == '+' || op == '-') && can_be_unary) {
                if (op == '-') op = '~'; 
                else continue;
            }
            
            while (!ops.empty() && ops.top() != '(' &&
                   ((get_precedence(ops.top()) > get_precedence(op)) ||
                    (get_precedence(ops.top()) == get_precedence(op) && op != '^'))) {
                apply_op(values, ops);
            }
            ops.push(op);
            can_be_unary = true;
        }
    }

    while (!ops.empty()) {
        apply_op(values, ops);
    }
    
    if (values.empty()) return 0;
    
    return values.top();
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void solve() {
    string line;
    while (getline(cin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        if (line == "end") break;

        if (line[0] == '?') {
            string var_name = trim(line.substr(1));
            cout << var_name << "=" << variables[var_name] << "\n";
        } else {
            size_t eq_pos = line.find('=');
            if (eq_pos != string::npos) {
                string var_name = trim(line.substr(0, eq_pos));
                string expr = trim(line.substr(eq_pos + 1));
                try {
                    variables[var_name] = evaluate(expr);
                } catch (const runtime_error& e) {
                    if (string(e.what()) == "Divide 0.") {
                        cout << "Divide 0." << "\n";
                    }
                }
            }
        }
    }
}

int main() {
    
    solve();

    return 0;
}