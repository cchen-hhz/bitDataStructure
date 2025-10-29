#include <bits/stdc++.h>
using namespace std;

int main() {
    int A_r, A_c, A_n;
    cin >> A_r >> A_c >> A_n;
    struct Trip { int r,c; long long v; };
    vector<Trip> A;
    A.reserve(A_n);
    for (int t = 0; t < A_n; ++t) {
        int i,j; long long v;
        cin >> i >> j >> v;
        A.push_back({i, j, v});
    }

    int B_r, B_c, B_n;
    cin >> B_r >> B_c >> B_n;
    vector<Trip> B;
    B.reserve(B_n);
    for (int t = 0; t < B_n; ++t) {
        int i,j; long long v;
        cin >> i >> j >> v;
        B.push_back({i, j, v});
    }

    vector<vector<pair<int,long long>>> Brow(B_r + 1);
    for (auto &t : B) {
        if (t.r >= 1 && t.r <= B_r)
            Brow[t.r].push_back({t.c, t.v});
    }
    int C_r = A_r, C_c = B_c;
    vector<map<int,long long>> Crows(C_r + 1); 

    for (auto &a : A) {
        int i = a.r;
        int j = a.c;
        long long aval = a.v;
        for (auto &p : Brow[j]) {
            int tcol = p.first;
            long long bval = p.second;
            long long add = aval * bval;
            auto &m = Crows[i];
            m[tcol] += add;
            if (m[tcol] == 0) m.erase(tcol); 
        }
    }

    vector<Trip> Cres;
    for (int i = 1; i <= C_r; ++i) {
        for (auto &kv : Crows[i]) {
            int col = kv.first;
            long long val = kv.second;
            if (val != 0) Cres.push_back({i, col, val});
        }
    }

    cout << C_r << "\n" << C_c << "\n" << (int)Cres.size() << "\n";
    for (auto &t : Cres) {
        cout << t.r << "," << t.c << "," << t.v << "\n";
    }

    return 0;
}