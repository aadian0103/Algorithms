vector<bool> pr;
vector<vector<int>> f;

void sieve(int n) {
    pr.assign(n + 1, true);

    for (int i = 2; i * i <= n; i++) {
        if (pr[i]) {
            for (int j = i * i; j <= N; j += i) {
                pr[j] = false;
            }
        }
    }
}

void factors(int n) {
    f.resize(n + 1);

    for (int i = 2; i * i <= n; i++) {
        if (f[i].empty()) {
            for (int j = i; j <= n; j += i) {
                f[j].emplace_back(i);
            }
        }
    }
}
