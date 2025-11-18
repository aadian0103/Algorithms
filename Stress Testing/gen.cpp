#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define debug(...)
#endif

#define nl '\n'
using ll = int64_t;
using ull = uint64_t;

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
T rnd(T a, T b) {
    uniform_int_distribution<T> dist(a, b);
    return dist(RNG);
}

vector<int> gen_vector(int n, int L, int R) {
    vector<int> a(n);
    for (int &x : a) x = rnd(L, R);
    return a;
}

vector<int> gen_perm(int n) {
    vector<int> p(n);
    ranges::iota(p, 1);
    ranges::shuffle(p, RNG);
    return p;
}

vector<pair<int,int>> gen_tree(int n) {
    vector<pair<int,int>> edges;
    edges.reserve(n - 1);

    for (int i = 2; i <= n; i++) {
        int p = rnd(1, i - 1);
        edges.emplace_back(p, i);
    }

    ranges::shuffle(edges, RNG);
    return edges;
}

vector<pair<int,int>> gen_graph(int n, int m, bool allow_self = false) {
    set<pair<int,int>> used;
    vector<pair<int,int>> edges;

    while ((int)edges.size() < m) {
        int u = rnd(1, n);
        int v = rnd(1, n);

        if (!allow_self && u == v) continue;
        if (used.insert({u, v}).second) edges.emplace_back(u, v);
    }
    return edges;
}

void solve() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}

