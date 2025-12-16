vector<int> pr, lp;

void Sieve(int n) {
    lp.assign(n + 1, 0);
    pr.clear();

    for (int i = 2; i <= n; i++) {
        if (lp[i] == 0){
            lp[i] = i;
            pr.emplace_back(i);
        }

        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    };
}

vector<pair<int, int>> Factors(int x) {
    vector<pair<int, int>> f;
    while (x > 1) {
        int p = lp[x], cnt = 0;
        while (lp[x] == p) {
            x /= p;
            cnt++;
        }
        f.emplace_back(p, cnt);
    }
    return f;
}
