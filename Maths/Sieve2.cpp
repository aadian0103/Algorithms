vector<bool> sieve;
vector<vector<int>> factors;

void Sieve(int n) {
    sieve.assign(n + 1, true);

    for (int i = 2; i * i <= n; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= N; j += i) {
                sieve[j] = false;
            }
        }
    }
}

void Factors(int n) {
    factors.resize(n + 1);

    for (int i = 2; i * i <= n; i++) {
        if (factors[i].empty()) {
            for (int j = i; j <= n; j += i) {
                factors[j].emplace_back(i);
            }
        }
    }
}
