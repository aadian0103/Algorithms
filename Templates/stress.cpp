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

void solve(){
    //generated randon value of n from l to r
    int n = rnd(1,8);

    //generating random vector having values from l to r
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        a[i] = rnd(1,100000);
    }

    //put you brute force solution in here
    auto brute = [&]() {


    };

    auto brute_ans = brute();

    //put you solution in here


    //compare both the answers and get the Test Case

    if (brute_ans != ans){
        cout << n << nl;
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << nl;
        cout << brute_ans << " " << ans << nl;
        exit(0);
    }
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
